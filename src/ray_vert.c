/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_vert.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shogura <shogura@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/29 15:20:23 by shogura           #+#    #+#             */
/*   Updated: 2022/09/29 18:22:34 by shogura          ###   ########.fr       */
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
	D->V.nextVertTouchX = D->x_intercept;
	D->V.nextVertTouchY = D->y_intercept;
}

void	intersection_vert(t_dda *D, t_data *dt, float rayAngle)
{
	float	x_to_check;
	float	y_to_check;

	calc_vert_delta(D, dt, rayAngle);
	while (D->V.nextVertTouchX >= 0 && D->V.nextVertTouchX
		<= g_window_w && D->V.nextVertTouchY >= 0
		&& D->V.nextVertTouchY <= g_window_h)
	{
		x_to_check = D->V.nextVertTouchX;
		if (D->facing_left)
			x_to_check -= 1;
		y_to_check = D->V.nextVertTouchY;
		if (map_has_wall_at(dt->t_map, x_to_check, y_to_check))
		{
			D->V.vertWallHitX = D->V.nextVertTouchX;
			D->V.vertWallHitY = D->V.nextVertTouchY;
			D->V.foundVertWallHit = true;
			D->V.vertWallContent = dt->t_map.content[(int)floor(y_to_check / TILESIZE)][(int)floor(x_to_check / TILESIZE)];
			break ;
		}
		else
		{
			D->V.nextVertTouchX += D->x_step;
			D->V.nextVertTouchY += D->y_step;
		}
	}
}
