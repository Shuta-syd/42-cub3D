/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hook_action.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shogura <shogura@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/14 20:58:18 by shogura           #+#    #+#             */
/*   Updated: 2022/09/29 15:17:42 by shogura          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3D.h>

/**
 * @ calculate player new X and Y
 */
void	move_player(t_data *dt, t_player *P)
{
	float	move_step;
	float	new_x;
	float	new_y;

	P->rotationAngle += P->turnDirection * P->turnSpeed;
	move_step = P->walkDirection * P->walkSpeed;
	new_x = P->x + cos(P->rotationAngle) * move_step;
	new_y = P->y + sin(P->rotationAngle) * move_step;
	if (map_has_wall_at(dt->Tmap, new_x, new_y) == false)
	{
		P->x = new_x;
		P->y = new_y;
	}
}

void	switch_direction(int keycode, t_player *P)
{
	if (keycode == UP)
	{
		P->turnDirection = 0;
		P->walkDirection = +1;
	}
	else if (keycode == DOWN)
	{
		P->turnDirection = 0;
		P->walkDirection = -1;
	}
	else if (keycode == ARROW_L)
	{
		P->walkDirection = 0;
		P->turnDirection = +1;
	}
	else if (keycode == ARROW_R)
	{
		P->walkDirection = 0;
		P->turnDirection = -1;
	}
}

/**
 * @ Key action to operate WSAD key
 */
int	key_action(int keycode, t_data *dt)
{
	t_player	*p;

	p = &dt->P;
	if (keycode == UP || keycode == DOWN || keycode == RIGHT
		|| keycode == LEFT || keycode == ARROW_L || keycode == ARROW_R)
	{
		switch_direction(keycode, p);
		move_player(dt, p);
		cast_all_rays(dt);
		render(dt);
	}
	else if (keycode == ESC)
		destroy_window(dt);
	return (0);
}

/**
 * @ hook action to delete window by esc or x button
 */
int	destroy_window(t_data *dt)
{
	mlx_destroy_window(dt->Tmlx.mlx, dt->Tmlx.win);
	ft_putstr_fd("[EXIT]\n", 2);
	exit(1);
	return (1);
}
