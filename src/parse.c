/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shogura <shogura@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/23 16:49:25 by shogura           #+#    #+#             */
/*   Updated: 2022/09/25 15:05:06 by shogura          ###   ########.fr       */
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

int	countLineLen(char *line)
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
	len = countLineLen(&line[i]) + 1;
	map->filepath[dir] = malloc(sizeof(char) * len);
	ft_strlcpy(map->filepath[dir], &line[i], len);
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
	while (line[i] && line[i] != '\n')
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

void countRowCol(t_map *map, t_list *lst)
{
	int		i;
	int		row;
	int		col;
	char	*content;

	col = 0;
	while (lst)
	{
		i = 0;
		row = 0;
		content = (char *)lst->content;
		while (content[i] && content[i] != '\n')
		{

			if (content[i] != ' ')
				row++;
			i++;
		}
		if (map->row < row)
			map->row = row;
		lst = lst->next;
		col++;
	}
	map->col = col;
}

void allocateMapMem(t_map *map)
{
	int	i;

	i = 0;
	map->content = ft_calloc(map->col, sizeof(char *));
	while (i < map->col)
	{
		map->content[i] = ft_calloc(map->row, sizeof(char));
		i++;
	}
}

void fetchMap(t_map *map)
{
	int	i;
	int	j;
	int	col;
	char *content;
	t_list *lst;

	j = 0;
	col = 0;
	lst = map->list;
	countRowCol(map, lst);
	allocateMapMem(map);
	while (lst)
	{
		i = 0;
		content = (char *)lst->content;
		while (content[i] && content[i] != '\n')
		{
			if (ft_isdigit(content[i]) && content[i] != ' ')
				map->content[col][j++] = content[i] - '0';
			else if (content[i] != ' ')
				map->content[col][j++] = POS;
			i++;
		}
		col++;
		lst = lst->next;
	}
}

bool adaptMapElement(t_map *map, char *line)
{
	int	i;

	i = 0;
	if (line == NULL)
		return (false);
	else if (line[i] == '\n' || line[i] == '\0')
		return (true);
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
	else
		ft_lstadd_back(&map->list, ft_lstnew(&line[i]));
	return (true);
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
		if (adaptMapElement(map, line) == false)
			break;
		free(line);
	}
	fetchMap(map);
	return ;
}

void parse(t_data *dt, const char *filepath)
{
	parseXpm(dt);
	parseMap(dt, filepath);
}
