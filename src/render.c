/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shogura <shogura@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/17 18:43:29 by shogura           #+#    #+#             */
/*   Updated: 2022/09/19 17:20:26 by shogura          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3D.h>

void renderTile(t_imgs *Timg, int tileX, int tileY, int color)
{
	int	endX;
	int	endY;

	endX = tileX + tileSize * MINIMAP_SCALE;
	endY = tileY + tileSize * MINIMAP_SCALE;
	for (int y = tileY; y < endY; y++)
		for (int x = tileX; x < endX; x++)
			my_mlx_pixel_put(&Timg->map, x, y, color);
}

void renderMap(t_data *dt)
{
	int color;

	for (int i = 0; i < mapRow; i++)
	{
		for (int j = 0; j < mapCol; j++)
		{
			int tileX = j * tileSize * MINIMAP_SCALE;
			int tileY = i * tileSize * MINIMAP_SCALE;
			if (map[i][j] == 1)
				color = calc_trgb(0, 255, 255, 255);
			else
				color = calc_trgb(0, 0, 0, 0);
			renderTile(&dt->Timg, tileX, tileY, color);
		}
	}
	mlx_put_image_to_window(dt->Tmlx.mlx, dt->Tmlx.win, dt->Timg.map.img, 0, 0);
}

void renderDrawLine(t_data *dt, float x, float y, float len, float angle, int color)
{
	float	plotX;
	float	plotY;

	x = (x + dt->P.width / 2) * MINIMAP_SCALE ;
	y = (y + dt->P.height / 2) * MINIMAP_SCALE;
	for (int l = 0; l < len * MINIMAP_SCALE; l++)
	{
		plotX = x + cos(angle) * l;
		plotY = y + sin(angle) * l;
		mlx_pixel_put(dt->Tmlx.mlx, dt->Tmlx.win, plotX, plotY, color);
	}
}

void renderPlayer(t_data *dt)
{
	float startX;
	float startY;
	float endX;
	float endY;

	startX = dt->P.x * MINIMAP_SCALE;
	startY = dt->P.y * MINIMAP_SCALE;
	endX = dt->P.width * MINIMAP_SCALE;
	endY = dt->P.height * MINIMAP_SCALE;
	for (int y = 0; y < endY; y++)
		for (int x = 0; x < endX; x++)
			my_mlx_pixel_put(&dt->Timg.P, x, y, 0xFF0000);
	mlx_put_image_to_window(dt->Tmlx.mlx, dt->Tmlx.win, dt->Timg.P.img, startX, startY);
	//renderDrawLine(dt, dt->P.x , dt->P.y, 50, dt->P.rotationAngle, 0xFF0000);
}


void renderRays(t_data *dt)
{
	int color = calc_trgb(0, 0, 255, 0);
	for (int i = 0; i < NUM_RAYS; i++)
		renderDrawLine(dt, dt->P.x, dt->P.y, dt->R[i].distance, dt->R[i].rayAngle, color);
}

int	render(t_data *dt)
{
	renderMap(dt);
	renderPlayer(dt);
	renderRays(dt);
	return (0);
}
