/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shogura <shogura@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/23 16:49:25 by shogura           #+#    #+#             */
/*   Updated: 2022/09/23 17:56:01 by shogura          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3D.h>

void	parseXpmData(t_data *dt, t_tex *tex, char *path)
{
	int	size;
	int	i;
	t_img xpm;

	i = -1;
	xpm.img = mlx_xpm_file_to_image(dt->Tmlx.mlx, path, &xpm.width, &xpm.height);
	size = xpm.width * xpm.height;
	tex->width = xpm.width;
	tex->height = xpm.height;
	xpm.data = (int *)mlx_get_data_addr(xpm.img, &xpm.bpp, &xpm.line_len, &xpm.endian);
	tex->data = (int *)malloc(sizeof(int) * tex->width * tex->height);
	while (++i < size)
		tex->data[i] = xpm.data[i];
	return ;
}

void	parseXpm(t_data *dt)
{
	int	i;
	const char *texturePath[] = {
		"./asset/xpm/wall01.xpm",
		NULL
};

	i = -1;
	while (texturePath[++i])
		parseXpmData(dt, &dt->tex[i], (char *)texturePath[i]);
}
