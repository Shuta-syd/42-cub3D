/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shogura <shogura@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/25 21:14:13 by shogura           #+#    #+#             */
/*   Updated: 2022/09/30 15:53:30 by shogura          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3D.h>

void	fetch_line_content(t_map *map, char *line)
{
	char *str;

	str = ft_strdup(line);
	if (str == NULL)
		ft_error(NULL, M_ERROR);
	ft_lstadd_back(&map->list, ft_lstnew(str));
}

void	dup_content_line(t_map *map, char *content, int col)
{
	int	i;
	int	row;

	i = 0;
	row = -1;
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
}

void	count_row_col(t_map *map, t_list *lst)
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
		col++;
		if (map->row < row)
			map->row = row;
		lst = lst->next;
	}
	map->col = col;
	if (col == 0)
		ft_error(NULL, "[ERROR] map content is nothing\n");
}

int	count_line(char *line)
{
	int	l;

	l = 0;
	while (line[l] && line[l] != ' ' && line[l] != '\n')
		l++;
	return (l);
}

void	allocate_map_mem(t_map *map)
{
	int	i;

	i = 0;
	map->content = ft_calloc(map->col, sizeof(int *));
	if (map->content == NULL)
		ft_error(NULL, M_ERROR);
	while (i < map->col)
	{
		map->content[i] = ft_calloc(map->row, sizeof(int));
		if (map->content[i] == NULL)
			ft_error(NULL, M_ERROR);
		i++;
	}
}
