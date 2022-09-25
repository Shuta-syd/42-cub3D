/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shogura <shogura@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/25 17:49:48 by shogura           #+#    #+#             */
/*   Updated: 2022/09/25 21:20:15 by shogura          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3D.h>

void	init_image(t_data *dt, t_imgs *Timg, t_mlx *M)
{
	t_img	*map;
	t_img	*map3d;
	t_img	*p;

	map = &Timg->map;
	p = &Timg->P;
	map3d = &Timg->map3D;
	map->img = mlx_new_image(M->mlx, WINDOW_W * MINIMAP_SCALE,
			WINDOW_H * MINIMAP_SCALE);
	map->addr = mlx_get_data_addr(map->img, &map->bpp,
			&map->line_len, &map->endian);
	p->img = mlx_new_image(M->mlx, dt->P.width * MINIMAP_SCALE,
			dt->P.height * MINIMAP_SCALE);
	p->addr = mlx_get_data_addr(p->img, &p->bpp, &p->line_len, &p->endian);
	map3d->img = mlx_new_image(M->mlx, WINDOW_W, WINDOW_H);
	map3d->addr = mlx_get_data_addr(map3d->img, &map3d->bpp,
		&map3d->line_len, &map3d->endian);
}

void	init_mlx(t_mlx *M)
{
	M->mlx = mlx_init();
	M->win = mlx_new_window(M->mlx, WINDOW_W, WINDOW_H, "cub3D");
}

void	init_player(t_player *P)
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
	init_mlx(&dt->Tmlx);
	init_player(&dt->P);
	init_image(dt, &dt->Timg, &dt->Tmlx);
}
