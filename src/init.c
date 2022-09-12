/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shogura <shogura@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/10 18:26:59 by shogura           #+#    #+#             */
/*   Updated: 2022/09/12 15:20:05 by shogura          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3D.h>

void init_mlx(t_data *dt)
{
	dt->Tmlx = malloc(sizeof(t_mlx));
	if (dt->Tmlx == NULL)
		ft_error(dt);
	dt->Tmlx->mlx = mlx_init();
	dt->Tmlx->win = mlx_new_window(dt->Tmlx->mlx, WIN_W, WIN_H, "miniRT");
}

void init(t_data *dt)
{
	init_mlx(dt);
}
