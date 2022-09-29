/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shogura <shogura@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/25 17:52:53 by shogura           #+#    #+#             */
/*   Updated: 2022/09/29 15:20:45 by shogura          ###   ########.fr       */
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
