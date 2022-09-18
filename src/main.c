/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shogura <shogura@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/09 20:25:04 by shogura           #+#    #+#             */
/*   Updated: 2022/09/17 18:26:34 by shogura          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3D.h>


int	main(void)
{
	t_data	*dt;

	dt = (t_data *)malloc(sizeof(t_data));
	if (dt == NULL)
		ft_error(NULL);
	init(dt);
	mlx_hook(dt->Tmlx.win, 2, 1L << 0, keyAction, dt);
	mlx_hook(dt->Tmlx.win, 17, 1L << 2, destroyWindow, dt);
	mlx_loop(dt->Tmlx.mlx);
	return 0;
}
