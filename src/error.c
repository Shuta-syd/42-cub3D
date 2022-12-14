/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shogura <shogura@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/29 19:33:05 by shogura           #+#    #+#             */
/*   Updated: 2022/10/04 17:44:07 by shogura          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3D.h>

void	is_all_wall(int *content, int row)
{
	int		i;
	bool	wall;

	i = -1;
	wall = true;
	while (++i < row)
	{
		if (content[i] == 0)
			wall = false;
	}
	if (wall == false)
		ft_error(NULL, "[ERROR] map content is something wrong\n");
}

void	wall_gap_check(int now, int prev, int i, t_map *map)
{
	if (prev <= now && i > 0)
	{
		while (prev++ < now)
			if (map->content[i][prev] != 1)
				ft_error(NULL, "[ERROR] map content is something wrong!\n");
	}
	else if (prev >= now && i > 0)
	{
		while (prev-- > now)
			if (map->content[i - 1][prev] != 1)
				ft_error(NULL, "[ERROR] map content is something wrong!\n");
	}
}

void	is_map_closed_walls(t_map *map)
{
	int	i;
	int	j;
	int	wall_index;
	int	wall_index_prev;

	i = -1;
	wall_index_prev = 0;
	while (++i < map->col)
	{
		j = -1;
		if (i == 0 || i == map->col - 1)
			is_all_wall(map->content[i], map->row);
		while (++j < map->row)
		{
			if (map->content[i][0] == 0)
				ft_error(NULL, "[ERROR] map content is something wrong\n");
			if (map->content[i][j] == 1)
				wall_index = j;
		}
		wall_gap_check(wall_index, wall_index_prev, i, map);
		wall_index_prev = wall_index;
	}
}

int	ft_error(t_data *dt, char *msg)
{
	(void)dt;
	ft_putstr_fd(msg, 2);
	exit(1);
	return (1);
}
