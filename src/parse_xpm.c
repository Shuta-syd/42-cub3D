/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_xpm.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shogura <shogura@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/25 17:35:26 by shogura           #+#    #+#             */
/*   Updated: 2022/09/30 14:14:56 by shogura          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3D.h>

void	parse_xpm_data(t_data *dt, t_tex *tex, char *path)
{
	int		x;
	int		y;
	t_img	xpm;

	x = -1;
	y = -1;
	xpm.img = mlx_xpm_file_to_image(dt->t_mlx.mlx, path,
			&xpm.width, &xpm.height);
	tex->width = xpm.width;
	tex->height = xpm.height;
	xpm.data = (int *)mlx_get_data_addr(xpm.img, &xpm.bpp,
			&xpm.line_len, &xpm.endian);
	tex->data = ft_calloc(tex->width * tex->height, sizeof(int));
	if (tex->data == NULL)
		ft_error(dt, M_ERROR);
	while (++x < tex->width)
	{
		y = -1;
		while (++y < tex->height)
			tex->data[TILESIZE * y + x] = xpm.data[TILESIZE * y + x];
	}
	mlx_destroy_image(dt->t_mlx.mlx, xpm.img);
	return;
}

void	parse_xpm(t_data *dt)
{
	int	i;

	i = 0;
	while (i < 4)
	{
		parse_xpm_data(dt, &dt->tex[i], dt->t_map.filepath[i]);
		i++;
	}
}
