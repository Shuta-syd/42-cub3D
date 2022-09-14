/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dda.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shogura <shogura@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/14 22:25:07 by shogura           #+#    #+#             */
/*   Updated: 2022/09/14 23:11:40 by shogura          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3D.h>

/**
 * @calculate ray position and direction
 */
void	calcRay(t_data *dt, int x)
{
	double cameraX = 2 * x / (double)screenWidth - 1; // x-coordinate in camera space
	dt->P.ray.x = dt->P.dir.x + dt->P.pl.x * cameraX;
	dt->P.ray.x = dt->P.dir.y + dt->P.pl.y * cameraX;
}

void calcStep(t_data *dt)
{
	if (dt->P.ray.x < 0)
	{
		dt->P.step.x = -1;
		dt->P.side.x = (dt->P.pos.x - dt->Tmap.x) * dt->P.dl.x;
	}
	else
	{
		dt->P.step.x = 1;
		dt->P.side.x = (dt->Tmap.x - dt->P.pos.x + 1) * dt->P.dl.x;
	}

	if (dt->P.ray.y < 0)
	{
		dt->P.step.y = -1;
		dt->P.side.y = (dt->P.pos.y - dt->Tmap.y) * dt->P.dl.y;
	}
	else
	{
		dt->P.step.y = 1;
		dt->P.side.y = (dt->Tmap.y - dt->P.pos.y + 1) * dt->P.dl.y;
	}
}

/**
 * @length of ray from one x or y-side to next x or y-side
 */
void setDelta(t_data *dt)
{
	if (dt->P.ray.x == 0)
		dt->P.dl.x = INFINITY;
	else
		dt->P.dl.x = fabs(1 / dt->P.ray.x);

	if (dt->P.ray.y == 0)
		dt->P.dl.y = INFINITY;
	else
		dt->P.dl.y = fabs(1 / dt->P.ray.y);
}

/**
 * @ loop until hit the wall
 */
void loopHit(t_data *dt)
{
	while (dt->hit == false)
	{
		// jump to next map square, either in x-direction, or in y-direction
		if (dt->P.side.x < dt->P.side.y)
		{
			dt->P.side.x += dt->P.dl.x;
			dt->Tmap.x += dt->P.step.x;
			dt->side = 0;
		}
		else
		{
			dt->P.side.y += dt->P.dl.y;
			dt->Tmap.y += dt->P.step.y;
			dt->side = 1;
		}
		// Check if ray has hit a wall
		if (worldMap[dt->Tmap.x][dt->Tmap.y] > 0)
			dt->hit = true;
	}
}

/**
 * @ Digital Differential Analyzer
 */
void	DDA(t_data *dt, int x)
{
	calcRay(dt, x);
	// which box of the map we're in
	dt->Tmap.x = (int)dt->P.pos.x;
	dt->Tmap.y = (int)dt->P.pos.y;
	setDelta(dt);
	calcStep(dt);
	loopHit(dt);
}
