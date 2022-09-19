/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shogura <shogura@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/19 15:23:51 by shogura           #+#    #+#             */
/*   Updated: 2022/09/19 16:15:01 by shogura          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3D.h>

/**
 * @ function to compress between 0~2π
 */
float normalizeAngle(float angle)
{
	angle = remainder(angle, M_PI * 2.0);
	if (angle < 0)
		angle = M_PI * 2.0 + angle;
	return angle;
}

void intersectionHorz(t_dda *D, t_data *dt, float rayAngle)
{
	D->yIntercept = floor(dt->P.y / tileSize) * tileSize;
	D->yIntercept += D->isRayFacingDown ? tileSize : 0;

	D->xIntercept = dt->P.x + (D->yIntercept - dt->P.y) / tan(rayAngle);

	D->yStep = tileSize;
	D->yStep *= D->isRayFacingUp ? -1 : 1;

	D->xStep = tileSize / tan(rayAngle);
	D->xStep *= (D->isRayFacingLeft && D->xStep > 0) ? -1 : 1;
	D->xStep *= (D->isRayFacingRight && D->xStep < 0) ? -1 : 1;

	D->H.nextHorzTouchX = D->xIntercept;
	D->H.nextHorzTouchY = D->yIntercept;

	while (D->H.nextHorzTouchX >= 0 && D->H.nextHorzTouchX <= WINDOW_W && D->H.nextHorzTouchY >= 0 && D->H.nextHorzTouchY <= WINDOW_H)
	{
		float xToCheck = D->H.nextHorzTouchX;
		float yToCheck = D->H.nextHorzTouchY + (D->isRayFacingUp ? -1 : 0);

		if (mapHasWallAt(xToCheck, yToCheck))
		{
			D->H.horzWallHitX = D->H.nextHorzTouchX;
			D->H.horzWallHitY = D->H.nextHorzTouchY;
			D->H.horzWallContent = map[(int)floor(yToCheck / tileSize)][(int)floor(xToCheck / tileSize)];
			D->H.foundHorzWallHit = true;
			break;
		}
		else
		{
			D->H.nextHorzTouchX += D->xStep;
			D->H.nextHorzTouchY += D->yStep;
		}
	}
}

void	cpmDistance(t_dda *D, t_data *dt, int stripId)
{
	float horzHitDistance;
	float vertHitDistance;

	if (D->H.foundHorzWallHit)
		horzHitDistance = distanceBetweenPoints(dt->P.x, dt->P.y, D->H.horzWallHitX, D->H.horzWallHitY);
	else
		horzHitDistance = INT_MAX;
	if (D->V.foundVertWallHit)
		vertHitDistance = distanceBetweenPoints(dt->P.x, dt->P.y, D->V.vertWallHitX, D->V.vertWallHitX);
	else
		vertHitDistance = INT_MAX;

	if (vertHitDistance <= horzHitDistance && vertHitDistance != INT_MAX)
	{
		dt->R[stripId].distance = vertHitDistance;
		dt->R[stripId].wallHitY = D->V.vertWallHitY;
		dt->R[stripId].wallHitX = D->V.vertWallHitX;
		dt->R[stripId].wallHitContent = D->V.vertWallContent;
		dt->R[stripId].wasHitVertical = true;
	}
	else if (vertHitDistance >= horzHitDistance && horzHitDistance != INT_MAX)
	{
		dt->R[stripId].distance = horzHitDistance;
		dt->R[stripId].wallHitX = D->H.horzWallHitX;
		dt->R[stripId].wallHitY = D->H.horzWallHitY;
		dt->R[stripId].wallHitContent = D->H.horzWallContent;
		dt->R[stripId].wasHitVertical = false;
	}
}

void intersectionVert(t_dda *D, t_data *dt, float rayAngle)
{
	D->xIntercept = floor(dt->P.x / tileSize) * tileSize;
	D->xIntercept += D->isRayFacingRight ? tileSize : 0;

	D->yIntercept = dt->P.y + (D->xIntercept - dt->P.x) * tan(rayAngle);

	D->xStep = tileSize;
	D->xStep *= D->isRayFacingLeft ? -1 : 1;

	D->yStep = tileSize * tan(rayAngle);
	D->yStep *= (D->isRayFacingUp && D->yStep > 0) ? -1 : 1;
	D->yStep *= (D->isRayFacingDown && D->yStep < 0) ? -1 : 1;

	D->V.nextVertTouchX = D->xIntercept;
	D->V.nextVertTouchY = D->yIntercept;

	while (D->V.nextVertTouchX >= 0 && D->V.nextVertTouchX <= WINDOW_W && D->V.nextVertTouchY >= 0 && D->V.nextVertTouchY <= WINDOW_H)
	{
		float xToCheck = D->V.nextVertTouchX + (D->isRayFacingLeft ? -1 : 0);
		float yToCheck = D->V.nextVertTouchY;

		if (mapHasWallAt(xToCheck, yToCheck))
		{
			D->V.vertWallHitX = D->V.nextVertTouchX;
			D->V.vertWallHitY = D->V.nextVertTouchY;
			D->V.foundVertWallHit = true;
			D->V.vertWallContent = map[(int)floor(yToCheck / tileSize)][(int)floor(xToCheck / tileSize)];
			break;
		}
		else
		{
			D->V.nextVertTouchX += D->xStep;
			D->V.nextVertTouchY += D->yStep;
		}
	}
}

void castRay(t_data *dt, float rayAngle, int stripId)
{
	t_dda	D;

	int isRayFacingDown = rayAngle > 0 && rayAngle < M_PI;
	int isRayFacingUp = !isRayFacingDown;
	int isRayFacingRight = rayAngle < 0.5 * M_PI || rayAngle > 1.5 * M_PI;
	int isRayFacingLeft = !isRayFacingRight;

	float xIntercept, yIntercept;
	float xStep, yStep;

	D.isRayFacingDown = rayAngle > 0 && rayAngle < M_PI;
	D.isRayFacingUp = !D.isRayFacingDown;
	D.isRayFacingRight = rayAngle < 0.5 * M_PI || rayAngle > 1.5 * M_PI;
	D.isRayFacingLeft = !D.isRayFacingRight;

	/**
	 * [HORIZONTAL RAY-GRID INTERSECTION CODE]
	 */
	D.H = (t_horz){};
	intersectionHorz(&D, dt, rayAngle);


	/**
	 * [VERTICAL RAY-GRID INTERSECTION CODE]
	 */
	//D.V = (t_vert){};
	int foundVertWallHit = false;
	float vertWallHitX = 0;
	float vertWallHitY = 0;
	int VertWallContent = 0;

	xIntercept = floor(dt->P.x / tileSize) * tileSize;
	xIntercept += isRayFacingRight ? tileSize : 0;

	yIntercept = dt->P.y + (xIntercept - dt->P.x) * tan(rayAngle);

	xStep = tileSize;
	xStep *= isRayFacingLeft ? -1 : 1;

	yStep = tileSize * tan(rayAngle);
	yStep *= (isRayFacingUp && yStep > 0) ? -1 : 1;
	yStep *= (isRayFacingDown && yStep < 0) ? -1 : 1;

	float nextVertTouchX = xIntercept;
	float nextVertTouchY = yIntercept;

	while (nextVertTouchX >= 0 && nextVertTouchX <= WINDOW_W && nextVertTouchY >= 0 && nextVertTouchY <= WINDOW_H)
	{
		float xToCheck = nextVertTouchX + (isRayFacingLeft ? -1 : 0);
		float yToCheck = nextVertTouchY;

		if (mapHasWallAt(xToCheck, yToCheck))
		{
			vertWallHitX = nextVertTouchX;
			vertWallHitY = nextVertTouchY;
			foundVertWallHit = true;
			VertWallContent = map[(int)floor(yToCheck / tileSize)][(int)floor(xToCheck / tileSize)];
			// printf("VERT x->[%f] y->[%f] content->[%d]\n", vertWallHitX, vertWallHitY, VertWallContent);
			mlx_pixel_put(dt->Tmlx.mlx, dt->Tmlx.win, vertWallHitX, vertWallHitY, 0x0000FF);
			break;
		}
		else
		{
			nextVertTouchX += xStep;
			nextVertTouchY += yStep;
		}
	}

	/**
	 *  Calculate both horizontal and vertical hit distances and choose the smallest one
	 */
	float horzHitDistance = D.H.foundHorzWallHit ? distanceBetweenPoints(dt->P.x, dt->P.y, D.H.horzWallHitX, D.H.horzWallHitY) : INT_MAX;
	// printf("horz distance->[%f] found->[%d]\n", horzHitDistance, foundHorzWallHit);

	float vertHitDistance = foundVertWallHit ? distanceBetweenPoints(dt->P.x, dt->P.y, vertWallHitX, vertWallHitY) : INT_MAX;
	// printf("vert distance->[%f] found->[%d]\n", vertHitDistance, foundVertWallHit);

	if (vertHitDistance <= horzHitDistance && vertHitDistance != INT_MAX)
	{
		dt->R[stripId].distance = vertHitDistance;
		dt->R[stripId].wallHitY = vertWallHitY;
		dt->R[stripId].wallHitX = vertWallHitX;
		dt->R[stripId].wallHitContent = VertWallContent;
		dt->R[stripId].wasHitVertical = true;
	}
	else if (vertHitDistance >= horzHitDistance && horzHitDistance != INT_MAX)
	{
		dt->R[stripId].distance = horzHitDistance;
		dt->R[stripId].wallHitX = D.H.horzWallHitX;
		dt->R[stripId].wallHitY = D.H.horzWallHitY;
		dt->R[stripId].wallHitContent = D.H.horzWallContent;
		dt->R[stripId].wasHitVertical = false;
	}
	/**
	 *  Calculate both horizontal and vertical hit distances and choose the smallest one
	 */
	//cpmDistance(&D, dt, stripId);

	dt->R[stripId].rayAngle = rayAngle;
	dt->R[stripId].isRayFacingUp = D.isRayFacingUp;
	dt->R[stripId].isRayFacingDown = D.isRayFacingDown;
	dt->R[stripId].isRayFacingLeft = D.isRayFacingLeft;
	dt->R[stripId].isRayFacingRight = D.isRayFacingRight;
}

/**
 * @ start first ray subtracting half of our FOV
 */
void castAllRays(t_data *dt)
{
	float rayAngle;

	rayAngle = dt->P.rotationAngle - (FOV_ANGLE / 2);
	for (int stripId = 0; stripId < NUM_RAYS; stripId++)
	{
		castRay(dt, normalizeAngle(rayAngle), stripId);
		rayAngle += FOV_ANGLE / NUM_RAYS;
	}
}
