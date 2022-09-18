/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shogura <shogura@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/17 18:43:29 by shogura           #+#    #+#             */
/*   Updated: 2022/09/18 16:49:19 by shogura          ###   ########.fr       */
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

void renderDrawLine(t_data *dt, float x, float y)
{
	float	plotX;
	float	plotY;
	float	len;

	len = 50; //hypothesis
	x += +dt->P.width / 2 * MINIMAP_SCALE;
	y += +dt->P.height / 2 * MINIMAP_SCALE;
	for (int l = 0; l < len; l++)
	{
		plotX = x + cos(dt->P.rotationAngle) * l * MINIMAP_SCALE;
		plotY = y + sin(dt->P.rotationAngle) * l * MINIMAP_SCALE;
		mlx_pixel_put(dt->Tmlx.mlx, dt->Tmlx.win, plotX, plotY, 0xFF0000);
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
	renderDrawLine(dt, startX, startY);
}

void castRay(t_data *dt, float rayAngle, float stripId)
{
	/**
	 * TODO: All that crazy logic for horz, vert ...
	 */

	
}

/**
 * @ start first ray subtracting half of our FOV
 */
void castAllRays(t_data *dt)
{
	float	rayAngle;

	rayAngle = dt->P.rotationAngle - (FOV_ANGLE / 2);
	for (int stripId = 0; stripId < NUM_RAYS; stripId++)
	{
		castRay(dt, rayAngle, stripId);
		rayAngle += FOV_ANGLE / NUM_RAYS;
	}
}

void renderRay(t_data *dt)
{
	(void)dt;
}

int	render(t_data *dt)
{
	renderMap(dt);
	renderPlayer(dt);
	renderRay(dt);
	return (0);
}
