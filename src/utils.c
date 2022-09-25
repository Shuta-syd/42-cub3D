/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shogura <shogura@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/25 17:47:31 by shogura           #+#    #+#             */
/*   Updated: 2022/09/25 20:09:13 by shogura          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3D.h>

void printMapStruct(t_map map);

/**
 * @ to put pixel to image
 */
void	my_mlx_pixel_put(t_img *img, int x, int y, int color)
{
	char	*dst;

	dst = img->addr + (y * img->line_len + x * (img->bpp / 8));
	*(unsigned int *)dst = color;
}

/**
 * @ calc trgb hex
 */
int	calc_trgb(unsigned char t, unsigned char r, unsigned char g, unsigned char b)
{
	return (t << 24 | r << 16 | g << 8 | b);
}

/**
 * @ Find the length of two points
 */
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

	if (x <= 0 || x >= WINDOW_W || y <= 0 || y > WINDOW_H)
		return true;
	mapX = floor(x / (float)tileSize);
	mapY = floor(y / (float)tileSize);
	if (map.content[mapY][mapX] == 1)
		return (true);
	return (false);
}
