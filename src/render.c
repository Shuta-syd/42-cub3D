/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shogura <shogura@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/17 18:43:29 by shogura           #+#    #+#             */
/*   Updated: 2022/09/29 15:44:59 by shogura          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3D.h>

void	render_minimap(t_data *dt)
{
	render_map(dt);
	render_player(dt, dt->P.x * MINIMAP_SCALE, dt->P.y * MINIMAP_SCALE);
	render_rays(dt);
}

int	render(t_data *dt)
{
	generate3d_projection(dt);
	mlx_put_image_to_window(dt->Tmlx.mlx, dt->Tmlx.win,
		dt->Timg.map3D.img, 0, 0);
	render_minimap(dt);
	return (0);
}
