/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shogura <shogura@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/25 17:52:53 by shogura           #+#    #+#             */
/*   Updated: 2022/09/30 14:06:19 by shogura          ###   ########.fr       */
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

	if (D->t_h.wall_hit)
		horz_hit_distance = distance_between_points(dt->t_p.x, dt->t_p.y,
				D->t_h.wall_hit_x, D->t_h.wall_hit_y);
	else
		horz_hit_distance = INT_MAX;
	if (D->t_v.wall_hit)
		vert_hit_distance = distance_between_points(dt->t_p.x, dt->t_p.y,
				D->t_v.wall_hit_x, D->t_v.wall_hit_y);
	else
		vert_hit_distance = INT_MAX;
	if (vert_hit_distance <= horz_hit_distance && vert_hit_distance != INT_MAX)
	{
		dt->t_r[stripId].distance = vert_hit_distance;
		dt->t_r[stripId].wall_hit_y = D->t_v.wall_hit_y;
		dt->t_r[stripId].wall_hit_x = D->t_v.wall_hit_x;
		dt->t_r[stripId].wall_hit_content = D->t_v.wall_content;
		dt->t_r[stripId].was_hit_vertical = true;
	}
	else if (vert_hit_distance >= horz_hit_distance
		&& horz_hit_distance != INT_MAX)
	{
		dt->t_r[stripId].distance = horz_hit_distance;
		dt->t_r[stripId].wall_hit_x = D->t_h.wall_hit_x;
		dt->t_r[stripId].wall_hit_y = D->t_h.wall_hit_y;
		dt->t_r[stripId].wall_hit_content = D->t_h.wall_content;
		dt->t_r[stripId].was_hit_vertical = false;
	}
}

void	cast_ray(t_data *dt, float rayAngle, int stripId)
{
	t_dda	*dda;

	dda = ft_calloc(1, sizeof(t_dda));
	if (dda == NULL)
		ft_error(dt, M_ERROR);
	dda->facing_down = rayAngle > 0 && rayAngle < M_PI;
	dda->facing_up = !dda->facing_down;
	dda->facing_right = rayAngle < 0.5 * M_PI
		|| rayAngle > 1.5 * M_PI;
	dda->facing_left = !dda->facing_right;
	intersection_horz(dda, dt, rayAngle);
	intersection_vert(dda, dt, rayAngle);
	cpm_distance(dda, dt, stripId);
	dt->t_r[stripId].ray_angle = rayAngle;
	dt->t_r[stripId].facing_up = dda->facing_up;
	dt->t_r[stripId].facing_down = dda->facing_down;
	dt->t_r[stripId].facing_left = dda->facing_left;
	dt->t_r[stripId].facing_right = dda->facing_right;
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
		ray_angle = dt->t_p.rotation_angle
			+ atan((col - g_num_rays / 2) / DIST_PROJ_PLANE);
		cast_ray(dt, normalize_angle(ray_angle), col);
		ray_angle += FOV_ANGLE / g_num_rays;
	}
}
