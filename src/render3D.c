/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render3D.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shogura <shogura@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/19 17:31:45 by shogura           #+#    #+#             */
/*   Updated: 2022/09/19 19:08:51 by shogura          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3D.h>

void	generate3DProjection(t_data *dt)
{
	int color = calc_trgb(255, 255, 255, 1);

	for (int i = 0; i < NUM_RAYS; i++)
	{
		float distanceProjPlane = (WINDOW_W / 2) / tan(FOV_ANGLE / 2); //distance from player to projection plane
		float projectedWallHeight = (tileSize / dt->R[i].distance * distanceProjPlane); // tileSize of the projection plane

		int wallStripHeight = (int)projectedWallHeight;

		int wallTopPixel = (WINDOW_H / 2) - (wallStripHeight / 2); // what does it mean???
		wallTopPixel = wallTopPixel < 0 ? 0 : wallTopPixel;

		int wallBottomPixel = (WINDOW_H / 2) + (wallStripHeight / 2);
		wallBottomPixel = wallBottomPixel > WINDOW_H ? WINDOW_H : wallBottomPixel;

		/**
		 * render the wall from wallTopPixel to wallBottomPixel
		 */
		for (int y = wallTopPixel; y < wallBottomPixel; y++)
			my_mlx_pixel_put(&dt->Timg.map3D, i, y, color);
	}
}
