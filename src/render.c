/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shogura <shogura@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/17 18:43:29 by shogura           #+#    #+#             */
/*   Updated: 2022/09/29 13:56:11 by shogura          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3D.h>

void	render_tile(t_imgs *Timg, int tileX, int tileY, int color)
{
	int	x;
	int	y;
	int	end_x;
	int	end_y;

	y = tileY - 1;
	end_x = tileX + tileSize * MINIMAP_SCALE;
	end_y = tileY + tileSize * MINIMAP_SCALE;
	while (++y < end_y)
	{
		x = tileX - 1;
		while (++x < end_x)
			my_mlx_pixel_put(&Timg->map, x, y, color);
	}
}

void	render_map(t_data *dt)
{
	int	i;
	int	j;
	int	color;

	i = -1;
	while (++i < dt->Tmap.col)
	{
		j = -1;
		while (++j < dt->Tmap.row)
		{
			int tileX = j * tileSize * MINIMAP_SCALE;
			int tileY = i * tileSize * MINIMAP_SCALE;
			if (dt->Tmap.content[i][j] == 1)
				color = calc_trgb(0, 255, 255, 255);
			else
				color = calc_trgb(0, 0, 0, 0);
			render_tile(&dt->Timg, tileX, tileY, color);
		}
	}
	mlx_put_image_to_window(dt->Tmlx.mlx, dt->Tmlx.win, dt->Timg.map.img, 0, 0);
}

void	renderDrawLine(t_data *dt, float x, float y, float len, float angle, int color)
{
	int		l;
	float	plotX;
	float	plotY;

	l = -1;
	x = (x + dt->P.width / 2) * MINIMAP_SCALE;
	y = (y + dt->P.height / 2) * MINIMAP_SCALE;
	while (++l < len * MINIMAP_SCALE)
	{
		plotX = x + cos(angle) * l;
		plotY = y + sin(angle) * l;
		mlx_pixel_put(dt->Tmlx.mlx, dt->Tmlx.win, plotX, plotY, color);
	}
}

void	render_player(t_data *dt, float startX, float startY)
{
	int	x;
	int	y;
	float	endX;
	float	endY;

	y = -1;
	endX = dt->P.width * MINIMAP_SCALE;
	endY = dt->P.height * MINIMAP_SCALE;
	while (++y < endY)
	{
		x = -1;
		while (++x < endX)
			my_mlx_pixel_put(&dt->Timg.P, x, y, 0xFF0000);
	}
	mlx_put_image_to_window(dt->Tmlx.mlx, dt->Tmlx.win, dt->Timg.P.img, startX, startY);
}

void	render_rays(t_data *dt)
{
	int	color;

	color = calc_trgb(0, 0, 255, 0);
	for (int i = 0; i < NUM_RAYS; i++)
		renderDrawLine(dt, dt->P.x, dt->P.y, dt->R[i].distance, dt->R[i].rayAngle, color);
}

int	render(t_data *dt)
{
	/**
	 * render 3D Texture
	 */
	generate3d_projection(dt);
	mlx_put_image_to_window(dt->Tmlx.mlx, dt->Tmlx.win, dt->Timg.map3D.img, 0, 0);

	/**
	 * render minimap
	 */
	render_map(dt);
	render_player(dt, dt->P.x * MINIMAP_SCALE, dt->P.y * MINIMAP_SCALE);
	render_rays(dt);
	return (0);
}
