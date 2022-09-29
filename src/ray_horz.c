/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_horz.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shogura <shogura@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/29 15:19:02 by shogura           #+#    #+#             */
/*   Updated: 2022/09/29 15:49:04 by shogura          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3D.h>

void	calc_horz_delta(t_dda *D, t_data *dt, float rayAngle)
{
	D->yIntercept = floor(dt->P.y / tileSize) * tileSize;
	if (D->isRayFacingDown)
		D->yIntercept += tileSize;
	D->xIntercept = dt->P.x + (D->yIntercept - dt->P.y) / tan(rayAngle);
	D->yStep = tileSize;
	if (D->isRayFacingUp)
		D->yStep *= -1;
	D->xStep = tileSize / tan(rayAngle);
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
	while (D->H.nextHorzTouchX >= 0 && D->H.nextHorzTouchX <= WINDOW_W
		&& D->H.nextHorzTouchY >= 0 && D->H.nextHorzTouchY <= WINDOW_H)
	{
		x_to_check = D->H.nextHorzTouchX;
		y_to_check = D->H.nextHorzTouchY;
		if (D->isRayFacingUp)
			y_to_check -= 1;
		if (map_has_wall_at(dt->Tmap, x_to_check, y_to_check))
		{
			D->H.horzWallHitX = D->H.nextHorzTouchX;
			D->H.horzWallHitY = D->H.nextHorzTouchY;
			D->H.horzWallContent = dt->Tmap.content[(int)floor(y_to_check / tileSize)][(int)floor(x_to_check / tileSize)];
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
