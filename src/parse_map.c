/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shogura <shogura@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/25 17:35:06 by shogura           #+#    #+#             */
/*   Updated: 2022/09/30 13:56:13 by shogura          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3D.h>

void	fetch_filepath(t_map *map, char *line, int dir)
{
	int	i;
	int	len;

	i = 0;
	while (line[i] && line[i] == ' ')
		i++;
	len = count_line(&line[i]) + 1;
	map->filepath[dir] = ft_calloc(len, sizeof(char));
	if (map->filepath[dir] == NULL)
		ft_error(NULL, M_ERROR); // check
	ft_strlcpy(map->filepath[dir], &line[i], len);
}

void	fetch_color(t_map *map, char *line, int type)
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

void	fetch_line_content(t_map *map, char *line)
{
	char	*str;

	str = ft_strdup(line);
	if (str == NULL)
		ft_error(NULL, M_ERROR);
	ft_lstadd_back(&map->list, ft_lstnew(str));
}

bool	adapt_map_element(t_map *map, char *line)
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
		fetch_filepath(map, &line[i + 2], NORTH);
	else if (ft_strnstr(&line[i], "SO", 2))
		fetch_filepath(map, &line[i + 2], SOUTH);
	else if (ft_strnstr(&line[i], "WE", 2))
		fetch_filepath(map, &line[i + 2], WEST);
	else if (ft_strnstr(&line[i], "EA", 2))
		fetch_filepath(map, &line[i + 2], EAST);
	else if (ft_strnstr(&line[i], "F", 1))
		fetch_color(map, &line[i + 1], 0);
	else if (ft_strnstr(&line[i], "C", 1))
		fetch_color(map, &line[i + 1], 1);
	else
		fetch_line_content(map, &line[i]);
	return (true);
}

void	fetch_map_info(t_map *map, t_list *lst)
{
	int		i;
	int		row;
	int		col;
	char	*content;

	col = 0;
	count_row_col(map, lst);
	allocate_map_mem(map);
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
			{
				map->content[col][++row] = 0;
				map->px = row * TILESIZE;
				map->py = col * TILESIZE;
			}
			i++;
		}
		while (i++ < map->row)
			map->content[col][++row] = NONE;
		col++;
		lst = lst->next;
	}
}

void	parse_map(t_data *dt, const char *filepath)
{
	int		fd;
	char	*line;
	t_map	*map;

	map = &dt->t_map;
	fd = open(filepath, O_RDONLY);
	if (fd < 0)
		ft_error(dt, "[ERROR] can not open file.");
	while (1)
	{
		line = get_next_line(fd);
		if (adapt_map_element(map, line) == false)
			break ;
		free(line);
	}
	fetch_map_info(map, map->list);
	return ;
}
