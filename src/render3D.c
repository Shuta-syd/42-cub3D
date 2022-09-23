/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render3D.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shogura <shogura@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/19 17:31:45 by shogura           #+#    #+#             */
/*   Updated: 2022/09/23 18:13:58 by shogura          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3D.h>

void	generate3DProjection(t_data *dt)
{

	for (int i = 0; i < NUM_RAYS; i++)
	{
		float distanceProjPlane = (WINDOW_W / 2) / tan(FOV_ANGLE / 2); //distance from player to projection plane
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


		for (int y = 0; y < wallTopPixel; y++)
			my_mlx_pixel_put(&dt->Timg.map3D, i, y, 0x99CCFF);

		for (int y = wallBottomPixel; y < WINDOW_H; y++)
			my_mlx_pixel_put(&dt->Timg.map3D, i, y, 0x9ecccc);
			// mlx_put_image_to_window(dt->Tmlx.mlx, dt->Tmlx.win, dt->Timg.t.img, i, y);

		for (int y = wallTopPixel; y < wallBottomPixel; y++)
			my_mlx_pixel_put(&dt->Timg.map3D, i, y, color);
	}
}
