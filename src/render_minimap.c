/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_minimap.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shogura <shogura@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/29 14:59:56 by shogura           #+#    #+#             */
/*   Updated: 2022/09/29 18:11:30 by shogura          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3D.h>

void	render_tile(t_imgs *t_img, int tileX, int tileY, int color)
{
	int	x;
	int	y;
	int	end_x;
	int	end_y;

	y = tileY - 1;
	end_x = tileX + TILESIZE * MINIMAP_SCALE;
	end_y = tileY + TILESIZE * MINIMAP_SCALE;
	while (++y < end_y)
	{
		x = tileX - 1;
		while (++x < end_x)
			my_mlx_pixel_put(&t_img->map, x, y, color);
	}
}

void	render_map(t_data *dt)
{
	int	i;
	int	j;
	int	color;
	int	tile_x;
	int	tile_y;

	i = -1;
	while (++i < dt->t_map.col)
	{
		j = -1;
		while (++j < dt->t_map.row)
		{
			tile_x = j * TILESIZE * MINIMAP_SCALE;
			tile_y = i * TILESIZE * MINIMAP_SCALE;
			if (dt->t_map.content[i][j] == 1)
				color = calc_trgb(0, 255, 255, 255);
			else if (dt->t_map.content[i][j] != 9)
				color = calc_trgb(0, 0, 0, 0);
			else
				color = 0xafafb0;
			render_tile(&dt->t_img, tile_x, tile_y, color);
		}
	}
	mlx_put_image_to_window(dt->t_mlx.mlx, dt->t_mlx.win, dt->t_img.map.img, 0, 0);
}

void	render_drawline(t_data *dt, float len, float angle)
{
	int		l;
	float	x;
	float	y;
	float	plot_x;
	float	plot_y;

	l = -1;
	x = (dt->t_p.x + dt->t_p.width / 2) * MINIMAP_SCALE;
	y = (dt->t_p.y + dt->t_p.height / 2) * MINIMAP_SCALE;
	while (++l < len * MINIMAP_SCALE)
	{
		plot_x = x + cos(angle) * l;
		plot_y = y + sin(angle) * l;
		mlx_pixel_put(dt->t_mlx.mlx, dt->t_mlx.win, plot_x, plot_y, 0x00ff00);
	}
}

void	render_player(t_data *dt, float startX, float startY)
{
	int		x;
	int		y;
	float	end_x;
	float	end_y;

	y = -1;
	end_x = dt->t_p.width * MINIMAP_SCALE;
	end_y = dt->t_p.height * MINIMAP_SCALE;
	while (++y < end_y)
	{
		x = -1;
		while (++x < end_x)
			my_mlx_pixel_put(&dt->t_img.P, x, y, 0xFF0000);
	}
	mlx_put_image_to_window(dt->t_mlx.mlx, dt->t_mlx.win,
		dt->t_img.P.img, startX, startY);
}

void	render_rays(t_data *dt)
{
	int	i;
	int	color;

	i = -1;
	while (++i < g_num_rays)
		render_drawline(dt, dt->t_r[i].distance, dt->t_r[i].ray_angle);
}
