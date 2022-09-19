/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render3D.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shogura <shogura@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/19 17:31:45 by shogura           #+#    #+#             */
/*   Updated: 2022/09/19 18:15:10 by shogura          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3D.h>

void	generate3DProjection(t_data *dt)
{
	for (int i = 0; i < NUM_RAYS; i++)
	{
		float distanceProjPlane = (WINDOW_W / 2) / tan(FOV_ANGLE / 2);
		float projectedWallHeight = (tileSize / dt->R[i].distance * distanceProjPlane);

		int wallStripHeight = (int)projectedWallHeight;

		int wallTopPixel = (WINDOW_H / 2) - (wallStripHeight / 2);
		wallTopPixel = wallTopPixel < 0 ? 0 : wallTopPixel;

		int wallBottomPixel = (WINDOW_H / 2) + (wallStripHeight / 2);
		wallBottomPixel = wallBottomPixel > WINDOW_H ? WINDOW_H : wallBottomPixel;

		/**
		 * render the wall from wallTopPixel to wallBottomPixel
		 */
		for (int y = wallTopPixel; y < wallBottomPixel; y++)
		{
			
		}

	}
}
