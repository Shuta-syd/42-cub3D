/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hook_action.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shogura <shogura@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/14 20:58:18 by shogura           #+#    #+#             */
/*   Updated: 2022/09/17 19:16:51 by shogura          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3D.h>

/**
 * @ Key action to operate WSAD key
 */
int	keyAction(int keycode, t_data *dt)
{
	(void)dt;
	if (keycode == KEY_W)
		;
	else if (keycode == KEY_A)
		;
	else if (keycode == KEY_S)
		;
	else if (keycode == KEY_D)
		;
	return (0);
}

/**
 * @ hook action to delete window by esc or x button
 */
int	destroyWindow(t_data *dt)
{
	mlx_destroy_window(dt->Tmlx.mlx, dt->Tmlx.win);
	ft_putstr("[EXIT]\n");
	exit(1);
	return (1);
}
