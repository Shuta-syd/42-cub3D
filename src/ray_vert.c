/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_vert.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shogura <shogura@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/29 15:20:23 by shogura           #+#    #+#             */
/*   Updated: 2022/09/29 15:50:05 by shogura          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3D.h>

void	calc_vert_delta(t_dda *D, t_data *dt, float rayAngle)
{
	D->xIntercept = floor(dt->P.x / tileSize) * tileSize;
	if (D->isRayFacingRight)
		D->xIntercept += tileSize;
	D->yIntercept = dt->P.y + (D->xIntercept - dt->P.x) * tan(rayAngle);
	D->xStep = tileSize;
	if (D->isRayFacingLeft)
		D->xStep *= -1;
	D->yStep = tileSize * tan(rayAngle);
	if (D->isRayFacingUp && D->yStep > 0)
		D->yStep *= -1;
	if (D->isRayFacingDown && D->yStep < 0)
		D->yStep *= -1;
	D->V.nextVertTouchX = D->xIntercept;
	D->V.nextVertTouchY = D->yIntercept;
}

void	intersection_vert(t_dda *D, t_data *dt, float rayAngle)
{
	float	x_to_check;
	float	y_to_check;

	calc_vert_delta(D, dt, rayAngle);
	while (D->V.nextVertTouchX >= 0 && D->V.nextVertTouchX
		<= WINDOW_W && D->V.nextVertTouchY >= 0
		&& D->V.nextVertTouchY <= WINDOW_H)
	{
		x_to_check = D->V.nextVertTouchX;
		if (D->isRayFacingLeft)
			x_to_check -= 1;
		y_to_check = D->V.nextVertTouchY;
		if (map_has_wall_at(dt->Tmap, x_to_check, y_to_check))
		{
			D->V.vertWallHitX = D->V.nextVertTouchX;
			D->V.vertWallHitY = D->V.nextVertTouchY;
			D->V.foundVertWallHit = true;
			D->V.vertWallContent = dt->Tmap.content[(int)floor(y_to_check / tileSize)][(int)floor(x_to_check / tileSize)];
			break ;
		}
		else
		{
			D->V.nextVertTouchX += D->xStep;
			D->V.nextVertTouchY += D->yStep;
		}
	}
}
