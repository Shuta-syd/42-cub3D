/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shogura <shogura@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/25 17:49:48 by shogura           #+#    #+#             */
/*   Updated: 2022/10/02 21:35:42 by shogura          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3D.h>

void	init_image(t_data *dt, t_imgs *Timg, t_mlx *M)
{
	t_img	*map;
	t_img	*map3d;
	t_img	*p;

	map = &Timg->map;
	p = &Timg->p;
	map3d = &Timg->map_3d;
	map->img = mlx_new_image(M->mlx, g_window_w * MINIMAP_SCALE,
			g_window_h * MINIMAP_SCALE);
	map->addr = mlx_get_data_addr(map->img, &map->bpp,
			&map->line_len, &map->endian);
	p->img = mlx_new_image(M->mlx, dt->t_p.width * MINIMAP_SCALE,
			dt->t_p.height * MINIMAP_SCALE);
	p->addr = mlx_get_data_addr(p->img, &p->bpp, &p->line_len, &p->endian);
	map3d->img = mlx_new_image(M->mlx, g_window_w, g_window_h);
	map3d->addr = mlx_get_data_addr(map3d->img, &map3d->bpp,
			&map3d->line_len, &map3d->endian);
}

void	init_mlx(t_mlx *M)
{
	M->mlx = mlx_init();
	M->win = mlx_new_window(M->mlx, g_window_w, g_window_h, "cub3D");
}

void	init_player(t_data *dt, t_player *P)
{
	P->x = dt->t_map.px;
	P->y = dt->t_map.py;
	P->width = 20;
	P->height = 20;
	P->turn_direction = 0;
	P->walk_direction = 0;
	P->rotation_angle = M_PI / 2;
	P->turn_speed = 100;
	P->walk_speed = 20;
}

void	init(t_data *dt)
{
	g_window_w = dt->t_map.row * TILESIZE;
	g_window_h = dt->t_map.col * TILESIZE;
	g_num_rays = g_window_w;
	dt->t_r = ft_calloc(g_num_rays, sizeof(t_ray));
	if (dt->t_r == NULL)
		ft_error(dt, M_ERROR);
	init_mlx(&dt->t_mlx);
	init_player(dt, &dt->t_p);
	init_image(dt, &dt->t_img, &dt->t_mlx);
}
