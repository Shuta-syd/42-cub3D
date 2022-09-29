/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render3D.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shogura <shogura@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/19 17:31:45 by shogura           #+#    #+#             */
/*   Updated: 2022/09/29 14:49:26 by shogura          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3D.h>
void printXpmData(t_tex *tex);

int *set_texture_direction(t_data *dt, t_ray ray)
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
	wall->distanceProjPlane = (WINDOW_W / 2) / tan(FOV_ANGLE / 2);
	wall->correctWallDistance = dt->R[i].distance * cos(dt->R[i].rayAngle - dt->P.rotationAngle);
	wall->projectedWallHeight = (tileSize / wall->correctWallDistance * wall->distanceProjPlane);
	wall->wallStripHeight = (int)wall->projectedWallHeight;
	wall->wallTopPixel = (WINDOW_H / 2) - (wall->wallStripHeight / 2);
	if (wall->wallTopPixel < 0)
		wall->wallTopPixel = 0;
	wall->wallBottomPixel = (WINDOW_H / 2) + (wall->wallStripHeight / 2);
	if (wall->wallBottomPixel > WINDOW_H)
		wall->wallBottomPixel = WINDOW_H;
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
		while (++y < WINDOW_H)
			my_mlx_pixel_put(&dt->Timg.map3D, i, y, dt->Tmap.floor);
	}

}

void render_3d_wall(t_data *dt, t_3d *wall, int i, int offsetX)
{
	int	y;
	int	offsetY;
	int	distanceFromTop;

	y = wall->wallTopPixel - 1;
	while (++y < wall->wallBottomPixel)
	{
		distanceFromTop = y + (wall->wallStripHeight / 2) - (WINDOW_H / 2);
		// why is tilesize casting by float type ?
		offsetY = distanceFromTop * ((float)tileSize / wall->wallStripHeight);
		wall->texture = set_texture_direction(dt, dt->R[i]);
		wall->texelColor = wall->texture[tileSize * offsetY + offsetX];
		my_mlx_pixel_put(&dt->Timg.map3D, i, y, wall->texelColor);
	}
}

void	generate3d_projection(t_data *dt)
{
	int		i;
	int		textureOffsetX;
	t_3d	wall;

	i = -1;
	while (++i < NUM_RAYS)
	{
		init_wall_projection(dt, &wall, i);
		render_cr(dt, &wall, i, true);
		if (dt->R[i].wasHitVertical)
			textureOffsetX = (int)dt->R[i].wallHitY % tileSize; // same 0
		else
			textureOffsetX = (int)dt->R[i].wallHitX % tileSize;
		render_3d_wall(dt, &wall, i, textureOffsetX);
		render_cr(dt, &wall, i, false);
	}
}
