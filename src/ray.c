/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shogura <shogura@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/25 17:52:53 by shogura           #+#    #+#             */
/*   Updated: 2022/09/30 16:29:02 by shogura          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3D.h>

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

void	copy_ray_info(t_dda *D, t_ray *R, float distance, bool isVert)
{
	if (isVert)
	{
		R->distance = distance;
		R->wall_hit_y = D->t_v.wall_hit_y;
		R->wall_hit_x = D->t_v.wall_hit_x;
		R->wall_hit_content = D->t_v.wall_content;
		R->was_hit_vertical = true;
	}
	else
	{
		R->distance = distance;
		R->wall_hit_x = D->t_h.wall_hit_x;
		R->wall_hit_y = D->t_h.wall_hit_y;
		R->wall_hit_content = D->t_h.wall_content;
		R->was_hit_vertical = false;
	}
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
		copy_ray_info(D, &dt->t_r[stripId], vert_hit_distance, true);
	else if (vert_hit_distance >= horz_hit_distance
		&& horz_hit_distance != INT_MAX)
		copy_ray_info(D, &dt->t_r[stripId], horz_hit_distance, false);
}

void	cast_ray(t_data *dt, float rayAngle, int stripId)
{
	t_dda	*dda;

	dda = ft_calloc(1, sizeof(t_dda));
	if (dda == NULL)
		ft_error(dt, M_ERROR);
	if (rayAngle > 0 && rayAngle < M_PI)
		dda->facing_down = 1;
	else
		dda->facing_down = 0;
	dda->facing_up = !dda->facing_down;
	if (rayAngle < 0.5 * M_PI || rayAngle > 1.5 * M_PI)
		dda->facing_right = 1;
	else
		dda->facing_right = 0;
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
	float	fov_angle;
	float	ray_angle;
	float	dist_proj_plane;

	col = -1;
	fov_angle = 60 * M_PI / 180;
	dist_proj_plane = (g_window_w / 2) / tan(fov_angle / 2);
	while (++col < g_num_rays)
	{
		ray_angle = dt->t_p.rotation_angle
			+ atan((col - g_num_rays / 2) / dist_proj_plane);
		cast_ray(dt, normalize_angle(ray_angle), col);
		ray_angle += fov_angle / g_num_rays;
	}
}
