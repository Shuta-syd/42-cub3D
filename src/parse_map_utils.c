/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shogura <shogura@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/25 21:14:13 by shogura           #+#    #+#             */
/*   Updated: 2022/09/30 13:39:15 by shogura          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3D.h>

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
