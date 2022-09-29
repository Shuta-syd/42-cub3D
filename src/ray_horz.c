/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_horz.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shogura <shogura@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/29 15:19:02 by shogura           #+#    #+#             */
/*   Updated: 2022/09/29 18:22:31 by shogura          ###   ########.fr       */
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
	D->H.nextHorzTouchX = D->x_intercept;
	D->H.nextHorzTouchY = D->y_intercept;
}

void	intersection_horz(t_dda *D, t_data *dt, float rayAngle)
{
	float	x_to_check;
	float	y_to_check;

	calc_horz_delta(D, dt, rayAngle);
	while (D->H.nextHorzTouchX >= 0 && D->H.nextHorzTouchX <= g_window_w && D->H.nextHorzTouchY >= 0 && D->H.nextHorzTouchY <= g_window_h)
	{
		x_to_check = D->H.nextHorzTouchX;
		y_to_check = D->H.nextHorzTouchY;
		if (D->facing_up)
			y_to_check -= 1;
		if (map_has_wall_at(dt->t_map, x_to_check, y_to_check))
		{
			if (y_to_check < 0)
				y_to_check = 0;
			D->H.horzWallHitX = D->H.nextHorzTouchX;
			D->H.horzWallHitY = D->H.nextHorzTouchY;
			D->H.horzWallContent = dt->t_map.content[(int)floor(y_to_check / TILESIZE)][(int)floor(x_to_check / TILESIZE)];
			D->H.foundHorzWallHit = true;
			break ;
		}
		else
		{
			D->H.nextHorzTouchX += D->x_step;
			D->H.nextHorzTouchY += D->y_step;
		}
	}
}
