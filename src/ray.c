/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shogura <shogura@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/25 17:52:53 by shogura           #+#    #+#             */
/*   Updated: 2022/09/29 17:59:58 by shogura          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3D.h>

void	print_mapStruct(t_map map);

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
	float	horz_hit_distance;
	float	vert_hit_distance;

	if (D->H.foundHorzWallHit)
		horz_hit_distance = distance_between_points(dt->P.x, dt->P.y,
				D->H.horzWallHitX, D->H.horzWallHitY);
	else
		horz_hit_distance = INT_MAX;
	if (D->V.foundVertWallHit)
		vert_hit_distance = distance_between_points(dt->P.x, dt->P.y,
				D->V.vertWallHitX, D->V.vertWallHitY);
	else
		vert_hit_distance = INT_MAX;
	if (vert_hit_distance <= horz_hit_distance && vert_hit_distance != INT_MAX)
	{
		dt->t_r[stripId].distance = vert_hit_distance;
		dt->t_r[stripId].wallHitY = D->V.vertWallHitY;
		dt->t_r[stripId].wallHitX = D->V.vertWallHitX;
		dt->t_r[stripId].wallHitContent = D->V.vertWallContent;
		dt->t_r[stripId].wasHitVertical = true;
	}
	else if (vert_hit_distance >= horz_hit_distance
		&& horz_hit_distance != INT_MAX)
	{
		dt->t_r[stripId].distance = horz_hit_distance;
		dt->t_r[stripId].wallHitX = D->H.horzWallHitX;
		dt->t_r[stripId].wallHitY = D->H.horzWallHitY;
		dt->t_r[stripId].wallHitContent = D->H.horzWallContent;
		dt->t_r[stripId].wasHitVertical = false;
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
	dt->t_r[stripId].rayAngle = rayAngle;
	dt->t_r[stripId].isRayFacingUp = dda->isRayFacingUp;
	dt->t_r[stripId].isRayFacingDown = dda->isRayFacingDown;
	dt->t_r[stripId].isRayFacingLeft = dda->isRayFacingLeft;
	dt->t_r[stripId].isRayFacingRight = dda->isRayFacingRight;
	free(dda);
}

/**
 * @ start first ray subtracting half of our FOV
 */
void	cast_all_rays(t_data *dt)
{
	int		col;
	float	ray_angle;

	col = -1;
	while (++col < g_num_rays)
	{
		ray_angle = dt->P.rotationAngle
			+ atan((col - g_num_rays / 2) / DIST_PROJ_PLANE);
		cast_ray(dt, normalize_angle(ray_angle), col);
		ray_angle += FOV_ANGLE / g_num_rays;
	}
}
