/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shogura <shogura@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/25 17:52:53 by shogura           #+#    #+#             */
/*   Updated: 2022/09/29 15:17:12 by shogura          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3D.h>

void	printMapStruct(t_map map);

/**
 * @ compress between 0~2π
 */
float	normalize_angle(float angle)
{
	angle = remainder(angle, M_PI * 2.0);
	if (angle < 0)
		angle = M_PI * 2.0 + angle;
	return (angle);
}

void	calc_horz_delta(t_dda *D, t_data *dt, float rayAngle)
{
	/**
	 * @ First intersection with Y axis
	 */
	D->yIntercept = floor(dt->P.y / tileSize) * tileSize;
	if (D->isRayFacingDown)
		D->yIntercept += tileSize;
	D->xIntercept = dt->P.x + (D->yIntercept - dt->P.y) / tan(rayAngle);

	/**
	 * @ Incremental width of the intersection with the y-axis to the next intersection
	 */
	D->yStep = tileSize;
	if (D->isRayFacingUp)
		D->yStep *= -1;
	D->xStep = tileSize / tan(rayAngle);
	if (D->isRayFacingLeft && D->xStep > 0)
		D->xStep *= -1;
	if (D->isRayFacingRight && D->xStep < 0)
		D->xStep *= -1;

	/**
	 * @ next intersection
	 */
	D->H.nextHorzTouchX = D->xIntercept;
	D->H.nextHorzTouchY = D->yIntercept;
}

void	intersection_horz(t_dda *D, t_data *dt, float rayAngle)
{
	float	x_to_check;
	float	y_to_check;

	calc_horz_delta(D, dt, rayAngle);
	/**
	 * @ loop until collide with a wall in the screen
	 */
	while (D->H.nextHorzTouchX >= 0 && D->H.nextHorzTouchX <= WINDOW_W
			&& D->H.nextHorzTouchY >= 0 && D->H.nextHorzTouchY <= WINDOW_H)
	{
		/**
		 * @ For program reasons, a point cannot be placed on the line, so -1 is used for consistency.
		 */
		x_to_check = D->H.nextHorzTouchX;
		y_to_check = D->H.nextHorzTouchY + (D->isRayFacingUp ? -1 : 0);

		if (map_has_wall_at(dt->Tmap, x_to_check, y_to_check))
		{
			D->H.horzWallHitX = D->H.nextHorzTouchX;
			D->H.horzWallHitY = D->H.nextHorzTouchY;
			D->H.horzWallContent = dt->Tmap.content[(int)floor(y_to_check / tileSize)][(int)floor(x_to_check / tileSize)];
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

void	calc_vert_delta(t_dda *D, t_data *dt, float rayAngle)
{
	/**
	 * @ First intersection with X axis
	 */
	D->xIntercept = floor(dt->P.x / tileSize) * tileSize;
	if (D->isRayFacingRight)
		D->xIntercept += tileSize;
	D->yIntercept = dt->P.y + (D->xIntercept - dt->P.x) * tan(rayAngle);

	/**
	 * @ Incremental width of the intersection with the x-axis to the next intersection
	 */
	D->xStep = tileSize;
	if (D->isRayFacingLeft)
		D->xStep *= -1;
	D->yStep = tileSize * tan(rayAngle);
	if (D->isRayFacingUp && D->yStep > 0)
		D->yStep *= -1;
	if (D->isRayFacingDown && D->yStep < 0)
		D->yStep *= -1;

	/**
	 * @ next intersection
	 */
	D->V.nextVertTouchX = D->xIntercept;
	D->V.nextVertTouchY = D->yIntercept;
}

void	intersection_vert(t_dda *D, t_data *dt, float rayAngle)
{
	float	x_to_check;
	float	y_to_check;

	calc_vert_delta(D, dt, rayAngle);
	/**
	 * @ loop until collide with a wall in the screen
	 */
	while (D->V.nextVertTouchX >= 0 && D->V.nextVertTouchX <= WINDOW_W
				&& D->V.nextVertTouchY >= 0 && D->V.nextVertTouchY <= WINDOW_H)
	{
		/**
		 * @ For program reasons, a point cannot be placed on the line, so -1 is used for consistency.
		 */
		x_to_check = D->V.nextVertTouchX + (D->isRayFacingLeft ? -1 : 0);
		y_to_check = D->V.nextVertTouchY;

		if (map_has_wall_at(dt->Tmap, x_to_check, y_to_check))
		{
			D->V.vertWallHitX = D->V.nextVertTouchX;
			D->V.vertWallHitY = D->V.nextVertTouchY;
			D->V.foundVertWallHit = true;
			D->V.vertWallContent = dt->Tmap.content[(int)floor(y_to_check / tileSize)][(int)floor(x_to_check / tileSize)];
			break;
		}
		else
		{
			D->V.nextVertTouchX += D->xStep;
			D->V.nextVertTouchY += D->yStep;
		}
	}
}

/**
 * @ Copy the closer intersection to dt
 */
void	cpm_distance(t_dda *D, t_data *dt, int stripId)
{
	float	horzHitDistance;
	float	vertHitDistance;

	if (D->H.foundHorzWallHit)
		horzHitDistance = distance_between_points(dt->P.x, dt->P.y, D->H.horzWallHitX, D->H.horzWallHitY);
	else
		horzHitDistance = INT_MAX;
	if (D->V.foundVertWallHit)
		vertHitDistance = distance_between_points(dt->P.x, dt->P.y, D->V.vertWallHitX, D->V.vertWallHitY);
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

void	cast_ray(t_data *dt, float rayAngle, int stripId)
{
	t_dda	*dda;

	dda = ft_calloc(1, sizeof(t_dda));
	dda->isRayFacingDown = rayAngle > 0
			&& rayAngle < M_PI;
	dda->isRayFacingUp = !dda->isRayFacingDown;
	dda->isRayFacingRight = rayAngle < 0.5 * M_PI
			|| rayAngle > 1.5 * M_PI;
	dda->isRayFacingLeft = !dda->isRayFacingRight;
	intersection_horz(dda, dt, rayAngle);
	intersection_vert(dda, dt, rayAngle);
	cpm_distance(dda, dt, stripId);
	dt->R[stripId].rayAngle = rayAngle;
	dt->R[stripId].isRayFacingUp = dda->isRayFacingUp;
	dt->R[stripId].isRayFacingDown = dda->isRayFacingDown;
	dt->R[stripId].isRayFacingLeft = dda->isRayFacingLeft;
	dt->R[stripId].isRayFacingRight = dda->isRayFacingRight;
	free(dda);
}

/**
 * @ start first ray subtracting half of our FOV
 */
void cast_all_rays(t_data *dt)
{
	int		col;
	float	rayAngle;

	col = -1;
	while (++col < NUM_RAYS)
	{
		rayAngle = dt->P.rotationAngle + atan((col - NUM_RAYS / 2) / DIST_PROJ_PLANE);
		cast_ray(dt, normalize_angle(rayAngle), col);
		rayAngle += FOV_ANGLE / NUM_RAYS;
	}
}
