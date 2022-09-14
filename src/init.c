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

void initImage(t_data *dt)
{
	(void)dt;
	// img->img = mlx_xpm_file_to_image(mlx, filepath, &size, &size);
}

void initMlx(t_data *dt)
{
	dt->Tmlx.mlx = mlx_init();
	dt->Tmlx.win = mlx_new_window(dt->Tmlx.mlx, screenWidth, screenHeight, "cub3D");
}

void initPlayer(t_data  *dt)
{
	// player start position
	dt->P.pos = (t_vec){22, 14};
	// initial direction
	dt->P.dir = (t_vec){-1, 0};
	// initial camera plane
	dt->P.pl = (t_vec){0, 0.66};
}

void init(t_data *dt)
{
	initMlx(dt);
	initPlayer(dt);
}
