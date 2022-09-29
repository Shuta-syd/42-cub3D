/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_vert.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shogura <shogura@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/29 15:20:23 by shogura           #+#    #+#             */
/*   Updated: 2022/09/29 19:02:16 by shogura          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3D.h>

void	calc_vert_delta(t_dda *D, t_data *dt, float rayAngle)
{
	D->x_intercept = floor(dt->t_p.x / TILESIZE) * TILESIZE;
	if (D->facing_right)
		D->x_intercept += TILESIZE;
	D->y_intercept = dt->t_p.y + (D->x_intercept - dt->t_p.x) * tan(rayAngle);
	D->x_step = TILESIZE;
	if (D->facing_left)
		D->x_step *= -1;
	D->y_step = TILESIZE * tan(rayAngle);
	if (D->facing_up && D->y_step > 0)
		D->y_step *= -1;
	if (D->facing_down && D->y_step < 0)
		D->y_step *= -1;
	D->V.next_x = D->x_intercept;
	D->V.next_y = D->y_intercept;
}

void	intersection_vert(t_dda *D, t_data *dt, float rayAngle)
{
	float	x_to_check;
	float	y_to_check;

	calc_vert_delta(D, dt, rayAngle);
	while (D->V.next_x >= 0 && D->V.next_x
		<= g_window_w && D->V.next_y >= 0
		&& D->V.next_y <= g_window_h)
	{
		x_to_check = D->V.next_x;
		if (D->facing_left)
			x_to_check -= 1;
		y_to_check = D->V.next_y;
		if (map_has_wall_at(dt->t_map, x_to_check, y_to_check))
		{
			D->V.wall_hit_x = D->V.next_x;
			D->V.wall_hit_y = D->V.next_y;
			D->V.wall_hit = true;
			D->V.wall_content = dt->t_map.content[(int)floor(y_to_check / TILESIZE)][(int)floor(x_to_check / TILESIZE)];
			break ;
		}
		else
		{
			D->V.next_x += D->x_step;
			D->V.next_y += D->y_step;
		}
	}
}
