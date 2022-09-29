/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shogura <shogura@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/25 17:31:41 by shogura           #+#    #+#             */
/*   Updated: 2022/09/29 17:33:56 by shogura          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3D.h>

void printMapStruct(t_map map)
{
	printf("WIN_W[%d] WIN_H[%d]\n", WINDOW_W, WINDOW_H);
	printf("rowX[%d] colY[%d] C[%d] F[%d]\n", map.row, map.col, map.ceiling, map.floor);
	for (size_t i = 0; i < 4; i++)
		printf("filepath[%zu] -> [%s]\n", i, map.filepath[i]);
	for (size_t i = 0; i < map.col; i++)
	{
		for (size_t j = 0; j < map.row; j++)
		{
			printf("%d", map.content[i][j]);
		}
		putchar('\n');
	}
}

int	main(int ac, char const *av[])
{
	t_data	*dt;

	if (ac != 2)
		return (1);
	dt = ft_calloc(1, sizeof(t_data));
	parse_map(dt, av[1]);
	init(dt);
	parse_xpm(dt);
	cast_all_rays(dt);
	render(dt);
	mlx_hook(dt->Tmlx.win, 2, 1L << 0, key_action, dt);
	mlx_hook(dt->Tmlx.win, 17, 1L << 2, destroy_window, dt);
	mlx_loop(dt->Tmlx.mlx);
	return (0);
}
