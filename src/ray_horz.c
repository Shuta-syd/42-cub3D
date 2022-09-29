/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_horz.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shogura <shogura@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/29 15:19:02 by shogura           #+#    #+#             */
/*   Updated: 2022/09/29 19:00:41 by shogura          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3D.h>

void	calc_horz_delta(t_dda *D, t_data *dt, float rayAngle)
{
	D->y_intercept = floor(dt->t_p.y / TILESIZE) * TILESIZE;
	if (D->facing_down)
		D->y_intercept += TILESIZE;
	D->x_intercept = dt->t_p.x + (D->y_intercept - dt->t_p.y) / tan(rayAngle);
	D->y_step = TILESIZE;
	if (D->facing_up)
		D->y_step *= -1;
	D->x_step = TILESIZE / tan(rayAngle);
	if (D->facing_left && D->x_step > 0)
		D->x_step *= -1;
	if (D->facing_right && D->x_step < 0)
		D->x_step *= -1;
	D->H.next_x = D->x_intercept;
	D->H.next_y = D->y_intercept;
}

void	intersection_horz(t_dda *D, t_data *dt, float rayAngle)
{
	float	x_to_check;
	float	y_to_check;

	calc_horz_delta(D, dt, rayAngle);
	while (D->H.next_x >= 0 && D->H.next_x <= g_window_w && D->H.next_y >= 0 && D->H.next_y <= g_window_h)
	{
		x_to_check = D->H.next_x;
		y_to_check = D->H.next_y;
		if (D->facing_up)
			y_to_check -= 1;
		if (map_has_wall_at(dt->t_map, x_to_check, y_to_check))
		{
			if (y_to_check < 0)
				y_to_check = 0;
			D->H.wall_hit_x = D->H.next_x;
			D->H.wall_hit_y = D->H.next_y;
			D->H.wall_content = dt->t_map.content[(int)floor(y_to_check / TILESIZE)][(int)floor(x_to_check / TILESIZE)];
			D->H.wall_hit = true;
			break ;
		}
		else
		{
			D->H.next_x += D->x_step;
			D->H.next_y += D->y_step;
		}
	}
}
