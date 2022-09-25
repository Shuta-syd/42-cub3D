/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shogura <shogura@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/19 15:24:07 by shogura           #+#    #+#             */
/*   Updated: 2022/09/25 17:23:13 by shogura          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3D.h>

float	distanceBetweenPoints(float x1, float y1, float x2, float y2)
{
	return (sqrt((x2 - x1) * (x2 - x1) + (y2 - y1) * (y2 - y1)));
}

/**
 * @ find weather there is (x, y) in wall
 */
bool	mapHasWallAt(t_map map, float x, float y)
{
	int	mapX;
	int	mapY;

	if (x < 0 || x > WINDOW_W || y < 0 || y > WINDOW_H)
		return true;
	mapX = floor(x / tileSize);
	mapY = floor(y / tileSize);
	return (map.content[mapY][mapX] == 1);
}
