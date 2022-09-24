/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shogura <shogura@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/23 16:49:25 by shogura           #+#    #+#             */
/*   Updated: 2022/09/24 19:12:38 by shogura          ###   ########.fr       */
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

void	fetchFilePath(t_map *map, char *line)
{
	int i;
	int	len;

	i = 0;
	while (line[i] == ' ')
		i++;
	len = i;
	while (line[])
	{
		/* code */
	}


}

void adaptMapElement(t_map *map, char *line)
{
	int	i;

	i = 0;
	while (line[i] == ' ')
		i++;
	if (ft_strnstr(&line[i], "NO", 2))
		fetchFilePath(map, &line[i]);
}

void parseMap(t_data *dt, const char *filepath)
{
	t_map	*map;
	int		fd;
	char	*line;

	map = &dt->Tmap;
	fd = open(filepath, O_RDONLY);
	while (1)
	{
		line = get_next_line(fd);
		adaptMapElement(map, line);
	}
	return ;
}

void parse(t_data *dt, const char *filepath)
{
	parseXpm(dt);
	parseMap(dt, filepath);
}
