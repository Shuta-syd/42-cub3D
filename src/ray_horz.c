/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_horz.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shogura <shogura@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/29 15:19:02 by shogura           #+#    #+#             */
/*   Updated: 2022/09/29 17:57:20 by shogura          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3D.h>

void	calc_horz_delta(t_dda *D, t_data *dt, float rayAngle)
{
	D->yIntercept = floor(dt->P.y / TILESIZE) * TILESIZE;
	if (D->isRayFacingDown)
		D->yIntercept += TILESIZE;
	D->xIntercept = dt->P.x + (D->yIntercept - dt->P.y) / tan(rayAngle);
	D->yStep = TILESIZE;
	if (D->isRayFacingUp)
		D->yStep *= -1;
	D->xStep = TILESIZE / tan(rayAngle);
	if (D->isRayFacingLeft && D->xStep > 0)
		D->xStep *= -1;
	if (D->isRayFacingRight && D->xStep < 0)
		D->xStep *= -1;
	D->H.nextHorzTouchX = D->xIntercept;
	D->H.nextHorzTouchY = D->yIntercept;
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
		if (D->isRayFacingUp)
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
			D->H.nextHorzTouchX += D->xStep;
			D->H.nextHorzTouchY += D->yStep;
		}
	}
}
