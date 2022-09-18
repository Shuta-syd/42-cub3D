/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shogura <shogura@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/17 18:43:29 by shogura           #+#    #+#             */
/*   Updated: 2022/09/18 13:06:56 by shogura          ###   ########.fr       */
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
			int tileX = j * tileSize;
			int tileY = i * tileSize;
			if (map[i][j] == 1)
				color = calc_trgb(0, 255, 255, 255);
			else
				color = calc_trgb(0, 0, 0, 0);
			renderTile(&dt->Timg, tileX * MINIMAP_SCALE, tileY * MINIMAP_SCALE, color);
		}
	}
	mlx_put_image_to_window(dt->Tmlx.mlx, dt->Tmlx.win, dt->Timg.map.img, 0, 0);
}
