/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hook_action.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shogura <shogura@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/14 20:58:18 by shogura           #+#    #+#             */
/*   Updated: 2022/09/18 15:40:27 by shogura          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3D.h>

void	movePlayer(t_data *dt, t_player *P)
{
	float moveStep;
	float	newX;
	float	newY;

	(void)dt;
	P->rotationAngle += P->turnDirection * P->turnSpeed;
	moveStep = P->walkDirection * P->walkSpeed;
	newX = P->x + cos(P->rotationAngle) * moveStep;
	newY = P->y + sin(P->rotationAngle) * moveStep;
	printf("a->%f step->%f x->%f y->%f\n", P->rotationAngle, moveStep, newX, newY);
	/**
	 * TODO:
	 * perform wall collision
	 */
	P->x = newX;
	P->y = newY;
}

void switchDirection(int keycode , t_player *P)
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
	else if (keycode == RIGHT)
	{
		P->walkDirection = 0;
		P->turnDirection = +1;
	}
	else if (keycode == LEFT)
	{
		P->walkDirection = 0;
		P->turnDirection = -1;
	}
}

/**
 * @ Key action to operate WSAD key
 */
int	keyAction(int keycode, t_data *dt)
{
	t_player *P;

	P = &dt->P;
	if (keycode == UP || keycode == DOWN || keycode == RIGHT || keycode == LEFT)
	{
		switchDirection(keycode, P);
		movePlayer(dt, P);
		render(dt);
	}
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
