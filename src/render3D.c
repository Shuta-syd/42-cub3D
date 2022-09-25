/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render3D.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shogura <shogura@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/19 17:31:45 by shogura           #+#    #+#             */
/*   Updated: 2022/09/25 20:32:46 by shogura          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3D.h>
void printXpmData(t_tex *tex);

int *setTextureDirection(t_data *dt, t_ray ray)
{
	if (ray.wasHitVertical && (dt->P.x - ray.wallHitX) > 0){
		return (dt->tex[WEST].data);
	}
	else if (ray.wasHitVertical && (dt->P.x - ray.wallHitX) < 0)
	{
		return (dt->tex[EAST].data);
	}
	else if (ray.wasHitVertical == false && (dt->P.y - ray.wallHitY) > 0)
	{

		return (dt->tex[NORTH].data);
	}
	else
	{
		return (dt->tex[SOUTH].data);
	}
}

void	generate3DProjection(t_data *dt)
{

	for (int i = 0; i < NUM_RAYS; i++)
	{
		float distanceProjPlane = (WINDOW_W / 2) / tan(FOV_ANGLE / 2); // distance from player to projection plane
		float correctWallDistance = dt->R[i].distance * cos(dt->R[i].rayAngle - dt->P.rotationAngle);
		float projectedWallHeight = (tileSize / correctWallDistance * distanceProjPlane); // tileSize of the projection plane

		int wallStripHeight = (int)projectedWallHeight;

		int wallTopPixel = (WINDOW_H / 2) - (wallStripHeight / 2); // what does it mean???
		wallTopPixel = wallTopPixel < 0 ? 0 : wallTopPixel;

		int wallBottomPixel = (WINDOW_H / 2) + (wallStripHeight / 2);
		wallBottomPixel = wallBottomPixel > WINDOW_H ? WINDOW_H : wallBottomPixel;

		/**
		 * render the wall from wallTopPixel to wallBottomPixel
		 */
		int color;
		if (dt->R[i].wasHitVertical)
			color = calc_trgb(0, 255, 255, 255);
		else
			color = calc_trgb(0, 204, 204, 204);

		// sailing
		for (int y = 0; y < wallTopPixel; y++)
			my_mlx_pixel_put(&dt->Timg.map3D, i, y, 0x99CCFF);

		int textureOffsetX;
		// calculate textureOffsetX
		if (dt->R[i].wasHitVertical)
			textureOffsetX = (int)dt->R[i].wallHitY % tileSize; // same 0
		else
			textureOffsetX = (int)dt->R[i].wallHitX % tileSize;

		// wall
		for (int y = wallTopPixel; y < wallBottomPixel; y++)
		{
			// calculate textureOffsetY
			int textureOffsetY;
			int distanceFromTop = y + (wallStripHeight / 2) - (WINDOW_H / 2);
			// why is tilesize casting by float type ?
			textureOffsetY = distanceFromTop * ((float)tileSize / wallStripHeight);

			int *texture = setTextureDirection(dt, dt->R[i]);

			int texelColor = texture[tileSize * textureOffsetY + textureOffsetX];
			my_mlx_pixel_put(&dt->Timg.map3D, i, y, texelColor);
		}

		// floor
		for (int y = wallBottomPixel; y < WINDOW_H; y++)
			my_mlx_pixel_put(&dt->Timg.map3D, i, y, 0x9ecccc);
	}
}
