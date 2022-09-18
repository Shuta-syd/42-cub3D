/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shogura <shogura@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/17 18:43:29 by shogura           #+#    #+#             */
/*   Updated: 2022/09/18 18:24:31 by shogura          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3D.h>

void renderTile(t_imgs *Timg, int tileX, int tileY, int color)
{
	int	endX;
	int	endY;

	endX = tileX + tileSize * MINIMAP_SCALE;
	endY = tileY + tileSize * MINIMAP_SCALE;
	for (int y = tileY; y < endY; y++)
		for (int x = tileX; x < endX; x++)
			my_mlx_pixel_put(&Timg->map, x, y, color);
}

void renderMap(t_data *dt)
{
	int color;

	for (int i = 0; i < mapRow; i++)
	{
		for (int j = 0; j < mapCol; j++)
		{
			int tileX = j * tileSize * MINIMAP_SCALE;
			int tileY = i * tileSize * MINIMAP_SCALE;
			if (map[i][j] == 1)
				color = calc_trgb(0, 255, 255, 255);
			else
				color = calc_trgb(0, 0, 0, 0);
			renderTile(&dt->Timg, tileX, tileY, color);
		}
	}
	mlx_put_image_to_window(dt->Tmlx.mlx, dt->Tmlx.win, dt->Timg.map.img, 0, 0);
}

void renderDrawLine(t_data *dt, float x, float y)
{
	float	plotX;
	float	plotY;
	float	len;

	len = 50; //hypothesis
	x += +dt->P.width / 2 * MINIMAP_SCALE;
	y += +dt->P.height / 2 * MINIMAP_SCALE;
	for (int l = 0; l < len; l++)
	{
		plotX = x + cos(dt->P.rotationAngle) * l * MINIMAP_SCALE;
		plotY = y + sin(dt->P.rotationAngle) * l * MINIMAP_SCALE;
		mlx_pixel_put(dt->Tmlx.mlx, dt->Tmlx.win, plotX, plotY, 0xFF0000);
	}
}

void renderPlayer(t_data *dt)
{
	float startX;
	float startY;
	float endX;
	float endY;

	startX = dt->P.x * MINIMAP_SCALE;
	startY = dt->P.y * MINIMAP_SCALE;
	endX = dt->P.width * MINIMAP_SCALE;
	endY = dt->P.height * MINIMAP_SCALE;
	for (int y = 0; y < endY; y++)
		for (int x = 0; x < endX; x++)
			my_mlx_pixel_put(&dt->Timg.P, x, y, 0xFF0000);
	mlx_put_image_to_window(dt->Tmlx.mlx, dt->Tmlx.win, dt->Timg.P.img, startX, startY);
	renderDrawLine(dt, startX, startY);
}

/**
 * @ what is this ?
 */
float normalizeAngle(float angle)
{
	angle = remainder(angle, M_PI * 2);
	if (angle < 0)
		angle = M_PI * 2 + angle;
	return angle;
}

float distanceBetweenPoints(float x1, float y1, float x2, float y2)
{
	return (sqrt((x2 - x1) * (x2 - x1) + (y2 - y1) * (y2 - y1)));
}

/**
 * TODO: All that crazy logic for horz, vert ...
 */
void castRay(t_data *dt, float rayAngle, int stripId)
{
	rayAngle = normalizeAngle(rayAngle);

	int	isRayFacingDown = rayAngle > 0 && rayAngle > M_PI;
	int	isRayFacingUp = !dt->R->isRayFacingDown;
	int	isRayFacingRight = rayAngle < 0.5 * M_PI || rayAngle > 1.5 * M_PI;
	int	isRayFacingLeft = !dt->R->isRayFacingRight;

	float xIntercept, yIntercept;
	float xStep, yStep;

	/**
	 * HORIZONTAL RAY-GRID INTERSECTION CODE
	 */
	int foundHorzWallHit = false;
	float horzWallHitX = 0;
	float horzWallHitY = 0;
	int horzWallContent = 0;

	xIntercept = floor(dt->P.x / tileSize) * tileSize;
	xIntercept += isRayFacingRight ? tileSize : 0;

	yIntercept = dt->P.y + (xIntercept - dt->P.x) / tan(rayAngle);

	xStep = tileSize;
	xStep *= isRayFacingLeft ? -1 : 1;

	yStep = tileSize / tan(rayAngle);
	yStep *= (isRayFacingUp && xStep > 0) ? -1 : 1;
	yStep *= (isRayFacingDown && xStep < 0) ? -1 : 1;

	float nextHorzTouchX = xIntercept;
	float nextHorzTouchY = yIntercept;

	while (nextHorzTouchX >= 0 && nextHorzTouchX <= WINDOW_W && nextHorzTouchX >= 0 && nextHorzTouchY <= WINDOW_H)
	{
		float xToCheck = nextHorzTouchX;
		float yToCheck = nextHorzTouchY + (isRayFacingUp ? -1 : 0);

		if (mapHasWallAt(xToCheck, yToCheck))
		{
			horzWallHitX = nextHorzTouchX;
			horzWallHitY = nextHorzTouchY;
			foundHorzWallHit = true;
			horzWallContent = map[(int)floor(yToCheck / tileSize)][(int)floor(xToCheck / tileSize)];
			break;
		}
		else
		{
			nextHorzTouchX += xStep;
			nextHorzTouchY += yStep;
		}

	}

	/**
	 * VERTICAL RAY-GRID INTERSECTION CODE
	 */
	int foundVertWallHit = false;
	float vertWallHitX = 0;
	float vertWallHitY = 0;
	int VertWallContent = 0;

	yIntercept = floor(dt->P.y / tileSize) * tileSize;
	yIntercept += isRayFacingDown ? tileSize : 0;

	xIntercept = dt->P.x + (yIntercept - dt->P.y) / tan(rayAngle);

	xStep = tileSize;
	xStep *= isRayFacingUp ? -1 : 1;

	yStep = tileSize / tan(rayAngle);
	yStep *= (isRayFacingLeft && xStep > 0) ? -1 : 1;
	yStep *= (isRayFacingRight && xStep < 0) ? -1 : 1;

	float nextVertTouchX = xIntercept;
	float nextVertTouchY = yIntercept;

	while (nextVertTouchX >= 0 && nextVertTouchX <= WINDOW_W && nextVertTouchX >= 0 && nextVertTouchY <= WINDOW_H)
	{
		float xToCheck = nextVertTouchX + (isRayFacingLeft ? -1 : 0);
		float yToCheck = nextVertTouchY;

		if (mapHasWallAt(xToCheck, yToCheck))
		{
			vertWallHitX = nextVertTouchX;
			vertWallHitY = nextVertTouchY;
			foundVertWallHit = true;
			VertWallContent = map[(int)floor(yToCheck / tileSize)][(int)floor(xToCheck / tileSize)];
			break;
		}
		else
		{
			nextVertTouchX += xStep;
			nextVertTouchY += yStep;
		}
	}
	/**
	 *  Calculate both horizontal and vertical hit distances and choose the smallest one
	 */

	float horzHitDistance = foundHorzWallHit ? distanceBetweenPoints(dt->P.x, dt->P.y, horzWallHitX, horzWallHitY) : INT_MAX;

	float vertHitDistance = foundVertWallHit ? distanceBetweenPoints(dt->P.x, dt->P.y, vertWallHitX, vertWallHitY) : INT_MAX;

	if (vertHitDistance < horzHitDistance)
	{
		dt->R[stripId].distance = vertHitDistance;
		dt->R[stripId].wallHitX = vertWallHitX;
		dt->R[stripId].wallHitY = vertWallHitY;
		dt->R[stripId].wallHitContent = VertWallContent;
		dt->R[stripId].wasHitVertical = true;
	}
	else
	{
		dt->R[stripId].distance = horzHitDistance;
		dt->R[stripId].wallHitX = horzWallHitX;
		dt->R[stripId].wallHitY = horzWallHitY;
		dt->R[stripId].wallHitContent = horzWallContent;
		dt->R[stripId].wasHitVertical = false;
	}
}

/**
 * @ start first ray subtracting half of our FOV
 */
void castAllRays(t_data * dt)
{
	float rayAngle;

	rayAngle = dt->P.rotationAngle - (FOV_ANGLE / 2);
	for (int stripId = 0; stripId < NUM_RAYS; stripId++)
	{
		castRay(dt, rayAngle, stripId);
		rayAngle += FOV_ANGLE / NUM_RAYS;
	}
}

void renderRay(t_data *dt)
{
	(void)dt;
}

int	render(t_data *dt)
{
	renderMap(dt);
	renderPlayer(dt);
	renderRay(dt);
	return (0);
}
