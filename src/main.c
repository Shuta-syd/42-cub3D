/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shogura <shogura@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/09 20:25:04 by shogura           #+#    #+#             */
/*   Updated: 2022/09/14 23:11:07 by shogura          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3D.h>

int	loop(t_data *dt)
{
	int	x;

	x = 0;
	while (x < screenWidth)
	{
		DDA(dt, x);
		x++;
	}
	return (0);
}

int	main(void)
{
	t_data	*dt;

	dt = (t_data *)malloc(sizeof(t_data));
	if (dt == NULL)
		ft_error(NULL);
	init(dt);
	mlx_loop_hook(dt->Tmlx.win, loop, dt);
	mlx_hook(dt->Tmlx.win, 2, 1L << 0, keyAction, dt);
	mlx_hook(dt->Tmlx.win, 17, 1L << 2, destroyWindow, dt);
	mlx_loop(dt->Tmlx.mlx);
	return 0;
}
