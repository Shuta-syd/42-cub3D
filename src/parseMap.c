/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parseMap.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shogura <shogura@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/25 17:35:06 by shogura           #+#    #+#             */
/*   Updated: 2022/09/25 17:46:46 by shogura          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3D.h>

void	countRowCol(t_map *map, t_list *lst)
{
	int	i;
	int	row;
	int	col;
	char *content;

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
		col++;
		if (map->row < row)
			map->row = row;
		lst = lst->next;
	}
	map->col = col;
}

int	countLineLen(char *line)
{
	int	l;

	l = 0;
	while (line[l] && line[l] != ' ' && line[l] != '\n')
		l++;
	return (l);
}

void	allocateMapMem(t_map *map)
{
	int	i;

	i = 0;
	map->content = ft_calloc(map->col, sizeof(int *));
	while (i < map->col)
	{
		map->content[i] = ft_calloc(map->row, sizeof(int));
		i++;
	}
}

void	fetchFilePath(t_map *map, char *line, int dir)
{
	int	i;
	int	len;

	i = 0;
	while (line[i] && line[i] == ' ')
		i++;
	len = countLineLen(&line[i]) + 1;
	map->filepath[dir] = malloc(sizeof(char) * len);
	ft_strlcpy(map->filepath[dir], &line[i], len);
}

void	fetchColor(t_map *map, char *line, int type)
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

bool	adaptMapElement(t_map *map, char *line)
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
		ft_lstadd_back(&map->list, ft_lstnew(ft_strdup(&line[i])));
	return (true);
}

void	fetchMap(t_map *map)
{
	int		i;
	int		row;
	int		col;
	char	*content;
	t_list	*lst;

	col = 0;
	lst = map->list;
	countRowCol(map, lst);
	allocateMapMem(map);
	while (lst)
	{
		i = 0;
		row = -1;
		content = (char *)lst->content;
		while (content[i] && content[i] != '\n')
		{
			if (ft_isdigit(content[i]) && content[i] != ' ')
				map->content[col][++row] = content[i] - '0';
			else if (content[i] != ' ')
				map->content[col][++row] = POS;
			i++;
		}
		col++;
		lst = lst->next;
	}
}

void	parseMap(t_data *dt, const char *filepath)
{
	int		fd;
	char	*line;
	t_map	*map;

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
	return;
}
