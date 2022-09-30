/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_vert.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shogura <shogura@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/29 15:20:23 by shogura           #+#    #+#             */
/*   Updated: 2022/09/30 16:12:33 by shogura          ###   ########.fr       */
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
	D->t_v.next_x = D->x_intercept;
	D->t_v.next_y = D->y_intercept;
}

bool	search_vert_intersection(t_dda *D, t_data *dt,
		float x_to_check, float y_to_check)
{
	int	x;
	int	y;

	if (map_has_wall_at(dt->t_map, x_to_check, y_to_check))
	{
		D->t_v.wall_hit_x = D->t_v.next_x;
		D->t_v.wall_hit_y = D->t_v.next_y;
		D->t_v.wall_hit = true;
		y = (int)floor(y_to_check / TILESIZE);
		x = (int)floor(x_to_check / TILESIZE);
		D->t_v.wall_content = dt->t_map.content[y][x];
		return (true);
	}
	else
	{
		D->t_v.next_x += D->x_step;
		D->t_v.next_y += D->y_step;
	}
	return (false);
}

void	intersection_vert(t_dda *D, t_data *dt, float rayAngle)
{
	float	x_to_check;
	float	y_to_check;

	calc_vert_delta(D, dt, rayAngle);
	while (D->t_v.next_x >= 0 && D->t_v.next_x
		<= g_window_w && D->t_v.next_y >= 0
		&& D->t_v.next_y <= g_window_h)
	{
		x_to_check = D->t_v.next_x;
		if (D->facing_left)
			x_to_check -= 1;
		y_to_check = D->t_v.next_y;
		if (search_vert_intersection(D, dt, x_to_check, y_to_check))
			return ;
	}
}
