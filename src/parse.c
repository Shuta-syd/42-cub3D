/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shogura <shogura@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/23 16:49:25 by shogura           #+#    #+#             */
/*   Updated: 2022/09/24 19:32:08 by shogura          ###   ########.fr       */
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

int	countCharOfFilePath(char *line)
{
	int	l;

	l = 0;
	while (line[l] && line[l] != ' ' && line[l] != '\n')
		l++;
	return (l);
}

void	fetchFilePath(t_map *map, char *line, int dir)
{
	int i;
	int	len;

	i = 0;
	while (line[i] && line[i] == ' ')
		i++;
	len = countCharOfFilePath(&line[i]);
	map->filepath[dir] = malloc(sizeof(char) * len + 1);
}

void fetchColor(t_map *map, char *line, int type)
{
	int	i;
	int	j;
	int	rgb[3];

	i = 0;
	j = 0;
	while (line[i] && line[i] == ' ')
		i++;
	while (line[i] && line[i] != ' \n')
	{
		rgb[j++] = ft_atoi(&line[i]);
		while (ft_isdigit(line[i]))
			i++;
		i++;
	}
	if (type == 0)
		map->floor = calc_trgb(0, rgb[0], rgb[1], rgb[2]);
	else if (type == 1)
		map->ceiling = calc_trgb(0, rgb[0], rgb[1], rgb[2]);
}

void adaptMapElement(t_map *map, char *line)
{
	int	i;

	i = 0;
	if (line[i] == '\n' || line[i] == '\0')
		return;
	while (line[i] && line[i] == ' ')
		i++;
	if (ft_strnstr(&line[i], "NO", 2))
		fetchFilePath(map, &line[i + 2], NORTH);
	else if (ft_strnstr(&line[i], "SO", 2))
		fetchFilePath(map, &line[i + 2], SOUTH);
	else if (ft_strnstr(&line[i], "WE", 2))
		fetchFilePath(map, &line[i + 2], WEST);
	else if (ft_strnstr(&line[i], "EA", 2))
		fetchFilePath(map, &line[i + 2], EAST);
	else if (ft_strnstr(&line[i], "F", 1))
		fetchColor(map, &line[i + 1], 0);
	else if (ft_strnstr(&line[i], "C", 1))
		fetchColor(map, &line[i + 1], 1);
	
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
