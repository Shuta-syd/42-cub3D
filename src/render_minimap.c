/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_minimap.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shogura <shogura@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/29 14:59:56 by shogura           #+#    #+#             */
/*   Updated: 2022/09/29 17:48:33 by shogura          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3D.h>

void	render_tile(t_imgs *Timg, int tileX, int tileY, int color)
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
			my_mlx_pixel_put(&Timg->map, x, y, color);
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
	while (++i < dt->Tmap.col)
	{
		j = -1;
		while (++j < dt->Tmap.row)
		{
			tile_x = j * TILESIZE * MINIMAP_SCALE;
			tile_y = i * TILESIZE * MINIMAP_SCALE;
			if (dt->Tmap.content[i][j] == 1)
				color = calc_trgb(0, 255, 255, 255);
			else if (dt->Tmap.content[i][j] != 9)
				color = calc_trgb(0, 0, 0, 0);
			else
				color = 0xafafb0;
			render_tile(&dt->Timg, tile_x, tile_y, color);
		}
	}
	mlx_put_image_to_window(dt->Tmlx.mlx, dt->Tmlx.win, dt->Timg.map.img, 0, 0);
}

void	render_drawline(t_data *dt, float len, float angle)
{
	int		l;
	float	x;
	float	y;
	float	plot_x;
	float	plot_y;

	l = -1;
	x = (dt->P.x + dt->P.width / 2) * MINIMAP_SCALE;
	y = (dt->P.y + dt->P.height / 2) * MINIMAP_SCALE;
	while (++l < len * MINIMAP_SCALE)
	{
		plot_x = x + cos(angle) * l;
		plot_y = y + sin(angle) * l;
		mlx_pixel_put(dt->Tmlx.mlx, dt->Tmlx.win, plot_x, plot_y, 0x00ff00);
	}
}

void	render_player(t_data *dt, float startX, float startY)
{
	int		x;
	int		y;
	float	end_x;
	float	end_y;

	y = -1;
	end_x = dt->P.width * MINIMAP_SCALE;
	end_y = dt->P.height * MINIMAP_SCALE;
	while (++y < end_y)
	{
		x = -1;
		while (++x < end_x)
			my_mlx_pixel_put(&dt->Timg.P, x, y, 0xFF0000);
	}
	mlx_put_image_to_window(dt->Tmlx.mlx, dt->Tmlx.win,
		dt->Timg.P.img, startX, startY);
}

void	render_rays(t_data *dt)
{
	int	i;
	int	color;

	i = -1;
	while (++i < g_num_rays)
		render_drawline(dt, dt->R[i].distance, dt->R[i].rayAngle);
}
