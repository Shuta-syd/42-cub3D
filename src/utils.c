/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shogura <shogura@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/25 17:47:31 by shogura           #+#    #+#             */
/*   Updated: 2022/09/29 16:41:52 by shogura          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3D.h>

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
int	calc_trgb(unsigned char t, unsigned char r,
		unsigned char g, unsigned char b)
{
	return (t << 24 | r << 16 | g << 8 | b);
}

/**
 * @ Find the length of two points
 */
float	distance_between_points(float x1, float y1, float x2, float y2)
{
	return (sqrt((x2 - x1) * (x2 - x1) + (y2 - y1) * (y2 - y1)));
}

/**
 * @ find weather there is (x, y) in wall
 */
bool	map_has_wall_at(t_map map, float x, float y)
{
	int	map_x;
	int	map_y;

	if (x <= 0 || x >= WINDOW_W || y <= 0 || y > WINDOW_H)
		return (true);
	map_x = floor(x / (float)tileSize);
	map_y = floor(y / (float)tileSize);
	if (map.content[map_y][map_x] == 1)
		return (true);
	return (false);
}
