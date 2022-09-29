/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render3D.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shogura <shogura@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/19 17:31:45 by shogura           #+#    #+#             */
/*   Updated: 2022/09/29 17:48:40 by shogura          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3D.h>

int	*set_texture_direction(t_data *dt, t_ray ray)
{
	if (ray.wasHitVertical && (dt->P.x - ray.wallHitX) > 0)
		return (dt->tex[WEST].data);
	else if (ray.wasHitVertical && (dt->P.x - ray.wallHitX) < 0)
		return (dt->tex[EAST].data);
	else if (ray.wasHitVertical == false && (dt->P.y - ray.wallHitY) > 0)
		return (dt->tex[NORTH].data);
	else
		return (dt->tex[SOUTH].data);
}

void	init_wall_projection(t_data *dt, t_3d *wall, int i)
{
	wall->distanceProjPlane = (g_window_w / 2) / tan(FOV_ANGLE / 2);
	wall->correctWallDistance = dt->R[i].distance
		* cos(dt->R[i].rayAngle - dt->P.rotationAngle);
	wall->projectedWallHeight = (TILESIZE / wall->correctWallDistance
			* wall->distanceProjPlane);
	wall->wallStripHeight = (int)wall->projectedWallHeight;
	wall->wallTopPixel = (g_window_h / 2) - (wall->wallStripHeight / 2);
	if (wall->wallTopPixel < 0)
		wall->wallTopPixel = 0;
	wall->wallBottomPixel = (g_window_h / 2) + (wall->wallStripHeight / 2);
	if (wall->wallBottomPixel > g_window_h)
		wall->wallBottomPixel = g_window_h;
}

void	render_cr(t_data *dt, t_3d *wall, int i, bool wasCeiling)
{
	int	y;

	if (wasCeiling)
	{
		y = -1;
		while (++y < wall->wallTopPixel)
			my_mlx_pixel_put(&dt->Timg.map3D, i, y, dt->Tmap.ceiling);
	}
	else
	{
		y = wall->wallBottomPixel - 1;
		while (++y < g_window_h)
			my_mlx_pixel_put(&dt->Timg.map3D, i, y, dt->Tmap.floor);
	}
}

void	render_3d_wall(t_data *dt, t_3d *wall, int i, int offsetX)
{
	int	y;
	int	offset_y;
	int	distance_from_top;

	y = wall->wallTopPixel - 1;
	while (++y < wall->wallBottomPixel)
	{
		distance_from_top = y + (wall->wallStripHeight / 2) - (g_window_h / 2);
		// why is TILESIZE casting by float type ?
		offset_y = distance_from_top * ((float)TILESIZE
				/ wall->wallStripHeight);
		wall->texture = set_texture_direction(dt, dt->R[i]);
		wall->texelColor = wall->texture[TILESIZE * offset_y + offsetX];
		my_mlx_pixel_put(&dt->Timg.map3D, i, y, wall->texelColor);
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
		if (dt->R[i].wasHitVertical)
			offset_x = (int)dt->R[i].wallHitY % TILESIZE;
		else
			offset_x = (int)dt->R[i].wallHitX % TILESIZE;
		render_3d_wall(dt, &wall, i, offset_x);
		render_cr(dt, &wall, i, false);
	}
}
