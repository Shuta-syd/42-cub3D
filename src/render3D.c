/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render3D.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shogura <shogura@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/19 17:31:45 by shogura           #+#    #+#             */
/*   Updated: 2022/09/29 19:08:20 by shogura          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3D.h>

int	*set_texture_direction(t_data *dt, t_ray ray)
{
	if (ray.was_hit_vertical && (dt->t_p.x - ray.wall_hit_x) > 0)
		return (dt->tex[WEST].data);
	else if (ray.was_hit_vertical && (dt->t_p.x - ray.wall_hit_x) < 0)
		return (dt->tex[EAST].data);
	else if (ray.was_hit_vertical == false && (dt->t_p.y - ray.wall_hit_y) > 0)
		return (dt->tex[NORTH].data);
	else
		return (dt->tex[SOUTH].data);
}

void	init_wall_projection(t_data *dt, t_3d *wall, int i)
{
	wall->distance_proj_plane = (g_window_w / 2) / tan(FOV_ANGLE / 2);
	wall->correct_wall_distance = dt->t_r[i].distance
		* cos(dt->t_r[i].ray_angle - dt->t_p.rotationAngle);
	wall->projected_wall_height = (TILESIZE / wall->correct_wall_distance
			* wall->distance_proj_plane);
	wall->wall_strip_height = (int)wall->projected_wall_height;
	wall->wall_top_pixel = (g_window_h / 2) - (wall->wall_strip_height / 2);
	if (wall->wall_top_pixel < 0)
		wall->wall_top_pixel = 0;
	wall->wall_bottom_pixel = (g_window_h / 2) + (wall->wall_strip_height / 2);
	if (wall->wall_bottom_pixel > g_window_h)
		wall->wall_bottom_pixel = g_window_h;
}

void	render_cr(t_data *dt, t_3d *wall, int i, bool wasCeiling)
{
	int	y;

	if (wasCeiling)
	{
		y = -1;
		while (++y < wall->wall_top_pixel)
			my_mlx_pixel_put(&dt->t_img.map3D, i, y, dt->t_map.ceiling);
	}
	else
	{
		y = wall->wall_bottom_pixel - 1;
		while (++y < g_window_h)
			my_mlx_pixel_put(&dt->t_img.map3D, i, y, dt->t_map.floor);
	}
}

void	render_3d_wall(t_data *dt, t_3d *wall, int i, int offsetX)
{
	int	y;
	int	offset_y;
	int	distance_from_top;

	y = wall->wall_top_pixel - 1;
	while (++y < wall->wall_bottom_pixel)
	{
		distance_from_top = y + (wall->wall_strip_height / 2) - (g_window_h / 2);
		// why is TILESIZE casting by float type ?
		offset_y = distance_from_top * ((float)TILESIZE
				/ wall->wall_strip_height);
		wall->texture = set_texture_direction(dt, dt->t_r[i]);
		wall->texel_color = wall->texture[TILESIZE * offset_y + offsetX];
		my_mlx_pixel_put(&dt->t_img.map3D, i, y, wall->texel_color);
	}
}

void	generate3d_projection(t_data *dt)
{
	int		i;
	int		offset_x;
	t_3d	wall;

	i = -1;
	while (++i < g_num_rays)
	{
		init_wall_projection(dt, &wall, i);
		render_cr(dt, &wall, i, true);
		if (dt->t_r[i].was_hit_vertical)
			offset_x = (int)dt->t_r[i].wall_hit_y % TILESIZE;
		else
			offset_x = (int)dt->t_r[i].wall_hit_x % TILESIZE;
		render_3d_wall(dt, &wall, i, offset_x);
		render_cr(dt, &wall, i, false);
	}
}
