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

const char basicMap[8][9] = {
	"11111111",
	"10100001",
	"10100101",
	"10000001",
	"10000001",
	"10P00101",
	"10000001",
	"11111111",
};

void init_mlx(t_data *dt)
{
	dt->Tmlx.mlx = mlx_init();
	dt->Tmlx.win = mlx_new_window(dt->Tmlx.mlx, WIN_W, WIN_H, "cub3D");
}

void init(t_data *dt)
{
	init_mlx(dt);
}
