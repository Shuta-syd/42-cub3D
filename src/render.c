/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shogura <shogura@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/17 18:43:29 by shogura           #+#    #+#             */
/*   Updated: 2022/09/25 20:40:21 by shogura          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3D.h>

void	renderTile(t_imgs *Timg, int tileX, int tileY, int color)
{
	int	endX;
	int	endY;

	endX = tileX + tileSize * MINIMAP_SCALE;
	endY = tileY + tileSize * MINIMAP_SCALE;
	for (int y = tileY; y < endY; y++)
		for (int x = tileX; x < endX; x++)
			my_mlx_pixel_put(&Timg->map, x, y, color);
}

void	renderMap(t_data *dt)
{
	int	color;

	for (int i = 0; i < dt->Tmap.col; i++)
	{
		for (int j = 0; j < dt->Tmap.row; j++)
		{
			int tileX = j * tileSize * MINIMAP_SCALE;
			int tileY = i * tileSize * MINIMAP_SCALE;
			if (dt->Tmap.content[i][j] == 1)
				color = calc_trgb(0, 255, 255, 255);
			else
				color = calc_trgb(0, 0, 0, 0);
			renderTile(&dt->Timg, tileX, tileY, color);
		}
	}
	mlx_put_image_to_window(dt->Tmlx.mlx, dt->Tmlx.win, dt->Timg.map.img, 0, 0);
}

void	renderDrawLine(t_data *dt, float x, float y, float len, float angle, int color)
{
	float	plotX;
	float	plotY;

	x = (x + dt->P.width / 2) * MINIMAP_SCALE;
	y = (y + dt->P.height / 2) * MINIMAP_SCALE;
	for (int l = 0; l < len * MINIMAP_SCALE; l++)
	{
		plotX = x + cos(angle) * l;
		plotY = y + sin(angle) * l;
		mlx_pixel_put(dt->Tmlx.mlx, dt->Tmlx.win, plotX, plotY, color);
	}
}

void	renderPlayer(t_data *dt)
{
	float	startX;
	float	startY;
	float	endX;
	float	endY;

	startX = dt->P.x * MINIMAP_SCALE;
	startY = dt->P.y * MINIMAP_SCALE;
	endX = dt->P.width * MINIMAP_SCALE;
	endY = dt->P.height * MINIMAP_SCALE;
	for (int y = 0; y < endY; y++)
		for (int x = 0; x < endX; x++)
			my_mlx_pixel_put(&dt->Timg.P, x, y, 0xFF0000);
	mlx_put_image_to_window(dt->Tmlx.mlx, dt->Tmlx.win, dt->Timg.P.img, startX, startY);
}

void	renderRays(t_data *dt)
{
	int	color;

	color = calc_trgb(0, 0, 255, 0);
	for (int i = 0; i < NUM_RAYS; i++)
		renderDrawLine(dt, dt->P.x, dt->P.y, dt->R[i].distance, dt->R[i].rayAngle, color);
}

void fillColorBuf(t_img *img, int width, int height, int color)
{
	for (int i = 0; i < height; i++)
		for (int j = 0; j < width; j++)
			my_mlx_pixel_put(img, j, i, color);
}

int	render(t_data *dt)
{
	/**
	 * render 3D Texture
	 */
	// fillColorBuf(&dt->Timg.map3D, WINDOW_W, WINDOW_H, 0x99CCFF);;
	generate3DProjection(dt);
	mlx_put_image_to_window(dt->Tmlx.mlx, dt->Tmlx.win, dt->Timg.map3D.img, 0, 0);

	/**
	 * render minimap
	 */
	renderMap(dt);
	renderPlayer(dt);
	renderRays(dt);
	return (0);
}
