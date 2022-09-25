/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shogura <shogura@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/25 17:49:48 by shogura           #+#    #+#             */
/*   Updated: 2022/09/25 20:00:55 by shogura          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3D.h>

void	initImage(t_data *dt, t_imgs *Timg, t_mlx *M)
{
	t_img	*map;
	t_img	*map3D;
	t_img	*P;

	map = &Timg->map;
	P = &Timg->P;
	map3D = &Timg->map3D;

	map->img = mlx_new_image(M->mlx, WINDOW_W * MINIMAP_SCALE, WINDOW_H * MINIMAP_SCALE);
	map->addr = mlx_get_data_addr(map->img, &map->bpp, &map->line_len, &map->endian);

	P->img = mlx_new_image(M->mlx, dt->P.width * MINIMAP_SCALE, dt->P.height * MINIMAP_SCALE);
	P->addr = mlx_get_data_addr(P->img, &P->bpp, &P->line_len, &P->endian);

	map3D->img = mlx_new_image(M->mlx, WINDOW_W, WINDOW_H);
	map3D->addr = mlx_get_data_addr(map3D->img, &map3D->bpp, &map3D->line_len, &map3D->endian);
}

void	initMlx(t_mlx *M)
{
	M->mlx = mlx_init();
	M->win = mlx_new_window(M->mlx, WINDOW_W, WINDOW_H, "cub3D");
}

void	initPlayer(t_player *P)
{
	P->x = WINDOW_W / 2;
	P->y = WINDOW_H / 2;
	P->width = 20;
	P->height = 20;
	P->turnDirection = 0;
	P->walkDirection = 0;
	P->rotationAngle = M_PI / 2;
	P->turnSpeed = 100;
	P->walkSpeed = 20;
}

void	init(t_data *dt)
{

	WINDOW_W = dt->Tmap.row * tileSize;
	WINDOW_H = dt->Tmap.col * tileSize;
	NUM_RAYS = WINDOW_W;

	initMlx(&dt->Tmlx);
	initPlayer(&dt->P);
	initImage(dt, &dt->Timg, &dt->Tmlx);
}
