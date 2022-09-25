/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shogura <shogura@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/19 15:23:51 by shogura           #+#    #+#             */
/*   Updated: 2022/09/25 17:22:09 by shogura          ###   ########.fr       */
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

		if (mapHasWallAt(dt->Tmap ,xToCheck, yToCheck))
		{
			D->H.horzWallHitX = D->H.nextHorzTouchX;
			D->H.horzWallHitY = D->H.nextHorzTouchY;
			D->H.horzWallContent = dt->Tmap.content[(int)floor(yToCheck / tileSize)][(int)floor(xToCheck / tileSize)];
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

		if (mapHasWallAt(dt->Tmap, xToCheck, yToCheck))
		{
			D->V.vertWallHitX = D->V.nextVertTouchX;
			D->V.vertWallHitY = D->V.nextVertTouchY;
			D->V.foundVertWallHit = true;
			D->V.vertWallContent = dt->Tmap.content[(int)floor(yToCheck / tileSize)][(int)floor(xToCheck / tileSize)];
			break;
		}
		else
		{
			D->V.nextVertTouchX += D->xStep;
			D->V.nextVertTouchY += D->yStep;
		}
	}
}

void cpmDistance(t_dda *D, t_data *dt, int stripId)
{
	float horzHitDistance;
	float vertHitDistance;

	if (D->H.foundHorzWallHit)
		horzHitDistance = distanceBetweenPoints(dt->P.x, dt->P.y, D->H.horzWallHitX, D->H.horzWallHitY);
	else
		horzHitDistance = INT_MAX;
	if (D->V.foundVertWallHit)
		vertHitDistance = distanceBetweenPoints(dt->P.x, dt->P.y, D->V.vertWallHitX, D->V.vertWallHitY);
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

void castRay(t_data *dt, float rayAngle, int stripId)
{
	t_dda	*D;

	D = malloc(sizeof(t_dda));
	D->isRayFacingDown = rayAngle > 0 && rayAngle < M_PI;
	D->isRayFacingUp = !D->isRayFacingDown;
	D->isRayFacingRight = rayAngle < 0.5 * M_PI || rayAngle > 1.5 * M_PI;
	D->isRayFacingLeft = !D->isRayFacingRight;

	/**
	 * [HORIZONTAL RAY-GRID INTERSECTION CODE]
	 */
	D->H = (t_horz){};
	intersectionHorz(D, dt, rayAngle);


	/**
	 * [VERTICAL RAY-GRID INTERSECTION CODE]
	 */
	D->V = (t_vert){};
	intersectionVert(D, dt, rayAngle);

	/**
	 * Calculate both horizontal and vertical hit distances and choose the smallest one
	 */
	cpmDistance(D, dt, stripId);
	dt->R[stripId].rayAngle = rayAngle;
	dt->R[stripId].isRayFacingUp = D->isRayFacingUp;
	dt->R[stripId].isRayFacingDown = D->isRayFacingDown;
	dt->R[stripId].isRayFacingLeft = D->isRayFacingLeft;
	dt->R[stripId].isRayFacingRight = D->isRayFacingRight;
}

/**
 * @ start first ray subtracting half of our FOV
 */
void castAllRays(t_data *dt)
{
	float rayAngle;

	for (int col = 0; col < NUM_RAYS; col++)
	{
		rayAngle = dt->P.rotationAngle + atan((col - NUM_RAYS / 2) / DIST_PROJ_PLANE);
		castRay(dt, normalizeAngle(rayAngle), col);
		rayAngle += FOV_ANGLE / NUM_RAYS;
	}
}
