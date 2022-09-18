/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shogura <shogura@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2"0"22/09/"1"0 "1"8:26:59 by shogura           #+#    #+#             */
/*   Updated: 2022/09/12 17:42:14 by shogura          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3D.h>

void initImage(t_imgs *Timg, t_mlx *M)
{
	t_img	*map;

	map = &Timg->map;
	map->img = mlx_new_image(M->mlx, WINDOW_W, WINDOW_H);
	map->addr = mlx_get_data_addr(map->img, &map->bpp, &map->line_len, &map->endian);
}

void initMlx(t_mlx *M)
{
	M->mlx = mlx_init();
	M->win = mlx_new_window(M->mlx, WINDOW_W, WINDOW_H, "cub3D");
}

void initPlayer(t_player *P)
{
	P->x = WINDOW_W / 2;
	P->y = WINDOW_H / 2;
	P->width = 5;
	P->height = 5;
	P->turnDirection = 0;
	P->walkDirection = 0;
	P->rotationAngle = M_PI / 2;
	P->walkDirection = 100;
	P->turnSpeed = 45;
}

void init(t_data *dt)
{
	initMlx(&dt->Tmlx);
	initImage(&dt->Timg, &dt->Tmlx);
	initPlayer(&dt->P);
}
