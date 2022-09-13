/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shogura <shogura@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/09 20:25:04 by shogura           #+#    #+#             */
/*   Updated: 2022/09/13 13:46:05 by shogura          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3D.h>

//delete window by esc or x button
int destroy_window(t_data *dt)
{
	mlx_destroy_window(dt->Tmlx.mlx, dt->Tmlx.win);
	ft_putstr("[EXIT]\n");
	exit(1);
}

void	ft_error(t_data *dt)
{
	(void)dt;
	write(2, ERROR, 24);
	exit(1);
}

void print(t_data *dt)
{
	(void)dt;
}

int	main(int argc, char const *argv[])
{
	(void)argc;
	(void)argv;
	t_data	*dt;

	dt = (t_data *)malloc(sizeof(t_data));
	if (dt == NULL)
		ft_error(NULL);
	init(dt);
	mlx_hook(dt->Tmlx.win, 17, 1L << 2, destroy_window, dt);
	mlx_loop(dt->Tmlx.mlx);
	return 0;
}
