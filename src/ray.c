/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shogura <shogura@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/25 17:52:53 by shogura           #+#    #+#             */
/*   Updated: 2022/09/25 20:10:20 by shogura          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3D.h>

void printMapStruct(t_map map);

/**
 * @ compress between 0~2π
 */
float	normalizeAngle(float angle)
{
	angle = remainder(angle, M_PI * 2.0);
	if (angle < 0)
		angle = M_PI * 2.0 + angle;
	return angle;
}

void intersectionHorz(t_dda *D, t_data *dt, float rayAngle)
{
	/**
	 * @ First intersection with Y axis
	 */
	D->yIntercept = floor(dt->P.y / tileSize) * tileSize;
	D->yIntercept += D->isRayFacingDown ? tileSize : 0;
	D->xIntercept = dt->P.x + (D->yIntercept - dt->P.y) / tan(rayAngle);

	/**
	 * @ Incremental width of the intersection with the y-axis to the next intersection
	 */
	D->yStep = tileSize;
	D->yStep *= D->isRayFacingUp ? -1 : 1;
	D->xStep = tileSize / tan(rayAngle);
	D->xStep *= (D->isRayFacingLeft && D->xStep > 0) ? -1 : 1;
	D->xStep *= (D->isRayFacingRight && D->xStep < 0) ? -1 : 1;

	/**
	 * @ next intersection
	 */
	D->H.nextHorzTouchX = D->xIntercept;
	D->H.nextHorzTouchY = D->yIntercept;

	/**
	 * @ loop until collide with a wall in the screen
	 */
	while (D->H.nextHorzTouchX >= 0 && D->H.nextHorzTouchX <= WINDOW_W && D->H.nextHorzTouchY >= 0 && D->H.nextHorzTouchY <= WINDOW_H)
	{
		/**
		 * @ For program reasons, a point cannot be placed on the line, so -1 is used for consistency.
		 */
		float xToCheck = D->H.nextHorzTouchX;
		float yToCheck = D->H.nextHorzTouchY + (D->isRayFacingUp ? -1 : 0);

		if (mapHasWallAt(dt->Tmap, xToCheck, yToCheck))
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

void	intersectionVert(t_dda *D, t_data *dt, float rayAngle)
{
	/**
	 * @ First intersection with X axis
	 */
	D->xIntercept = floor(dt->P.x / tileSize) * tileSize;
	D->xIntercept += D->isRayFacingRight ? tileSize : 0;
	D->yIntercept = dt->P.y + (D->xIntercept - dt->P.x) * tan(rayAngle);

	/**
	 * @ Incremental width of the intersection with the x-axis to the next intersection
	 */
	D->xStep = tileSize;
	D->xStep *= D->isRayFacingLeft ? -1 : 1;
	D->yStep = tileSize * tan(rayAngle);
	D->yStep *= (D->isRayFacingUp && D->yStep > 0) ? -1 : 1;
	D->yStep *= (D->isRayFacingDown && D->yStep < 0) ? -1 : 1;

	/**
	 * @ next intersection
	 */
	D->V.nextVertTouchX = D->xIntercept;
	D->V.nextVertTouchY = D->yIntercept;

	/**
	 * @ loop until collide with a wall in the screen
	 */
	while (D->V.nextVertTouchX >= 0 && D->V.nextVertTouchX <= WINDOW_W && D->V.nextVertTouchY >= 0 && D->V.nextVertTouchY <= WINDOW_H)
	{
		/**
		 * @ For program reasons, a point cannot be placed on the line, so -1 is used for consistency.
		 */
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

void	cpmDistance(t_dda *D, t_data *dt, int stripId)
{
	float	horzHitDistance;
	float	vertHitDistance;

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

void	castRay(t_data *dt, float rayAngle, int stripId)
{
	t_dda	*D;

	D = ft_calloc(1, sizeof(t_dda));
	D->isRayFacingDown = rayAngle > 0 && rayAngle < M_PI;
	D->isRayFacingUp = !D->isRayFacingDown;
	D->isRayFacingRight = rayAngle < 0.5 * M_PI || rayAngle > 1.5 * M_PI;
	D->isRayFacingLeft = !D->isRayFacingRight;
	intersectionHorz(D, dt, rayAngle);
	intersectionVert(D, dt, rayAngle);
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
	int		col;
	float	rayAngle;

	col = -1;
	while (++col < NUM_RAYS)
	{
		rayAngle = dt->P.rotationAngle + atan((col - NUM_RAYS / 2) / DIST_PROJ_PLANE);
		castRay(dt, normalizeAngle(rayAngle), col);
		rayAngle += FOV_ANGLE / NUM_RAYS;
	}
}
