/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shogura <shogura@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/17 18:43:29 by shogura           #+#    #+#             */
/*   Updated: 2022/10/03 21:45:10 by shogura          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3D.h>

void	render_minimap(t_data *dt)
{
	render_map(dt);
	render_player(dt, dt->t_p.x * MINIMAP_SCALE, dt->t_p.y * MINIMAP_SCALE);
	render_rays(dt);
}

int	render(t_data *dt)
{
	generate3d_projection(dt);
	mlx_put_image_to_window(dt->t_mlx.mlx, dt->t_mlx.win,
		dt->t_img.map_3d.img, 0, 0);
	render_minimap(dt);
	return (0);
}
