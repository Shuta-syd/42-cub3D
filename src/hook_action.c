/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hook_action.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shogura <shogura@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/14 20:58:18 by shogura           #+#    #+#             */
/*   Updated: 2022/09/19 12:00:59 by shogura          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3D.h>

bool mapHasWallAt(float x, float y)
{
	int	mapX;
	int	mapY;
	if (x < 0 || x > WINDOW_W || y < 0 || y > WINDOW_H)
		return true;
	mapX = floor(x / tileSize);
	mapY = floor(y / tileSize);
	return map[mapY][mapX] == 1;
}

void	movePlayer(t_player *P)
{
	float moveStep;
	float	newX;
	float	newY;

	P->rotationAngle += P->turnDirection * P->turnSpeed;
	moveStep = P->walkDirection * P->walkSpeed;
	newX = P->x + cos(P->rotationAngle) * moveStep;
	newY = P->y + sin(P->rotationAngle) * moveStep;
	if (mapHasWallAt(newX, newY) == false)
	{
		P->x = newX;
		P->y = newY;
	}
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
		movePlayer(P);
		castAllRays(dt);
		render(dt);
	}
	else if (keycode == ESC)
		destroyWindow(dt);
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
