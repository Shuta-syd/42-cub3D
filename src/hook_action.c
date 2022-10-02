/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hook_action.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shogura <shogura@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/14 20:58:18 by shogura           #+#    #+#             */
/*   Updated: 2022/10/02 21:34:58 by shogura          ###   ########.fr       */
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

	P->rotation_angle += P->turn_direction * P->turn_speed;
	move_step = P->walk_direction * P->walk_speed;
	new_x = P->x + cos(P->rotation_angle) * move_step;
	new_y = P->y + sin(P->rotation_angle) * move_step;
	if (map_has_wall_at(dt->t_map, new_x, new_y) == false)
	{
		P->x = new_x;
		P->y = new_y;
	}
}

void	move_player_lr(t_data *dt, t_player *P)
{
	float	move_step;
	float	new_x;
	float	new_y;
	float	angle;

	angle = P->rotation_angle + M_PI / 2;
	move_step = P->walk_direction * P->walk_speed;
	new_x = P->x + cos(angle) * move_step;
	new_y = P->y + sin(angle) * move_step;
	if (map_has_wall_at(dt->t_map, new_x, new_y) == false)
	{
		P->x = new_x;
		P->y = new_y;
	}
}

void	switch_direction(int keycode, t_player *P)
{
	wasd(keycode, P);
	arrow_key(keycode, P);
}

/**
 * @ Key action to operate WSAD key
 */
int	key_action(int keycode, t_data *dt)
{
	t_player	*p;

	p = &dt->t_p;
	if (keycode == UP || keycode == DOWN || keycode == ARROW_L || keycode == ARROW_R)
	{
		switch_direction(keycode, p);
		move_player(dt, p);
		cast_all_rays(dt);
		render(dt);
	}
	else if (keycode == RIGHT || keycode == LEFT)
	{
		switch_direction(keycode, p);
		move_player_lr(dt, p);
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
	mlx_destroy_window(dt->t_mlx.mlx, dt->t_mlx.win);
	ft_putstr_fd("[EXIT]\n", 2);
	exit(1);
	return (1);
}
