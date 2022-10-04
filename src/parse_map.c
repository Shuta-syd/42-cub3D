/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shogura <shogura@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/25 17:35:06 by shogura           #+#    #+#             */
/*   Updated: 2022/10/04 17:45:00 by shogura          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3D.h>

void	fetch_filepath(t_map *map, char *line, int dir)
{
	int	i;
	int	len;
	int	fd;

	i = 0;
	while (line[i] && line[i] == ' ')
		i++;
	len = count_line(&line[i]) + 1;
	map->filepath[dir] = ft_calloc(len, sizeof(char));
	if (map->filepath[dir] == NULL)
		ft_error(NULL, M_ERROR);
	ft_strlcpy(map->filepath[dir], &line[i], len);
	fd = open(map->filepath[dir], O_RDONLY);
	if (fd < 0)
		ft_error(NULL, F_ERROR);
	close(fd);
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
		rgb[j] = ft_atoi(&line[i]);
		if (rgb[j] > 255)
			ft_error(NULL, "[ERROR] rgb num is out of range \n");
		j++;
		while (line[i] && ft_isdigit(line[i]))
			i++;
		while (line[i] && (line[i] == ',' || line[i] == ' '))
			i++;
	}
	if (type == 0)
		map->floor = calc_trgb(0, rgb[0], rgb[1], rgb[2]);
	else if (type == 1)
		map->ceiling = calc_trgb(0, rgb[0], rgb[1], rgb[2]);
}

bool	adapt_map_element(t_map *map, char *line)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	if (line == NULL)
		return (false);
	j = i;
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
		fetch_line_content(map, &line[j]);
	return (true);
}

void	fetch_map_info(t_map *map, t_list *lst)
{
	int		col;

	col = 0;
	count_row_col(map, lst);
	allocate_map_mem(map);
	while (lst)
	{
		dup_content_line(map, (char *)lst->content, col);
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
	while (1)
	{
		line = get_next_line(fd);
		if (line && (line[0] == '\n' || line[0] == '\0'))
			;
		else if (adapt_map_element(map, line) == false)
			break ;
		free(line);
	}
	fetch_map_info(map, map->list);
	is_map_closed_walls(map);
	if (fd < 0)
		ft_error(dt, F_ERROR);
	close(fd);
	return ;
}
