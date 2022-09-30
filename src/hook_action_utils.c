/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hook_action_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shogura <shogura@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/30 15:55:32 by shogura           #+#    #+#             */
/*   Updated: 2022/09/30 15:55:46 by shogura          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3D.h>

void	wasd(int keycode, t_player *P)
{
	if (keycode == UP)
	{
		P->turn_direction = 0;
		P->walk_direction = +1;
	}
	else if (keycode == DOWN)
	{
		P->turn_direction = 0;
		P->walk_direction = -1;
	}
	else if (keycode == RIGHT)
	{
		P->turn_direction = -0.5;
		P->walk_direction = 1;
	}
	else if (keycode == LEFT)
	{
		P->turn_direction = 0.5;
		P->walk_direction = 1;
	}
}

void	arrow_key(int keycode, t_player *P)
{
	if (keycode == ARROW_L)
	{
		P->walk_direction = 0;
		P->turn_direction = +1;
	}
	else if (keycode == ARROW_R)
	{
		P->walk_direction = 0;
		P->turn_direction = -1;
	}
}
