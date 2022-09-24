/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shogura <shogura@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/23 16:49:25 by shogura           #+#    #+#             */
/*   Updated: 2022/09/24 16:50:57 by shogura          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3D.h>

void	parseXpmData(t_data *dt, t_tex *tex, char *path)
{
	int		x;
	int		y;
	t_img	xpm;

	x = -1;
	y = -1;
	xpm.img = mlx_xpm_file_to_image(dt->Tmlx.mlx, path, &xpm.width, &xpm.height);
	tex->width = xpm.width;
	tex->height = xpm.height;
	xpm.data = (int *)mlx_get_data_addr(xpm.img, &xpm.bpp, &xpm.line_len, &xpm.endian);
	tex->data = (int *)malloc(sizeof(int) * tex->width * tex->height);
	while (++x < tex->width)
	{
		y = -1;
		while (++y < tex->height)
			tex->data[tileSize * y + x] = xpm.data[tileSize * y + x];
	}
	return ;
}

void	parseXpm(t_data *dt)
{
	int	i;
	const char *texturePath[] = {
		"./asset/xpm/wall02_north.xpm",
		"./asset/xpm/wall02_south.xpm",
		"./asset/xpm/wall02_west.xpm",
		"./asset/xpm/wall02_east.xpm",
		NULL
};

	i = -1;
	while (texturePath[++i])
		parseXpmData(dt, &dt->tex[i], (char *)texturePath[i]);
}
