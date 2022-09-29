/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shogura <shogura@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/17 18:43:29 by shogura           #+#    #+#             */
/*   Updated: 2022/09/29 17:58:12 by shogura          ###   ########.fr       */
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
	mlx_put_image_to_window(dt->t_mlx.mlx, dt->t_mlx.win,
		dt->t_img.map3D.img, 0, 0);
	render_minimap(dt);
	return (0);
}
