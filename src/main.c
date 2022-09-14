/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shogura <shogura@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/09 20:25:04 by shogura           #+#    #+#             */
/*   Updated: 2022/09/14 13:51:33 by shogura          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3D.h>

const char basicMap[8][9] = {
	"11111111",
	"10100001",
	"10100101",
	"10000001",
	"10000001",
	"10000101",
	"10000001",
	"11111111"};

//delete window by esc or x button
int destroyWindow(t_data *dt)
{
	mlx_destroy_window(dt->Tmlx.mlx, dt->Tmlx.win);
	ft_putstr("[EXIT]\n");
	exit(1);
	return (1);
}

void	ft_error(t_data *dt)
{
	(void)dt;
	write(2, ERROR, 24);
	exit(1);
}

void	my_mlx_pixel_put(t_img *img, int x, int y, int color)
{
	char *dst;

	dst = img->addr + (y * img->line_len + x * (img->bpp / 8));
	*(unsigned int *)dst = color;
}

float calcHypotenuse(float sx, float sy, float ex, float ey)
{
	float h;
	float bottom;
	float height;

	bottom = sx - ex;
	if (bottom < 0)
		bottom *= -1;
	height = sy - ey;
	if (height < 0)
		height *= -1;
	h = pow(bottom, 2) + pow(height, 2);
	return (sqrt(h));
}

void drawDiagonal(t_data * dt, float x, float y)
{
	x += 7.5;
	y += 7.5;
	float len = calcHypotenuse(x, y, x + dt->Tvec.dx * 15, y + dt->Tvec.dy * 15);
	for (float l = 0; l < len; l++)
	{
		float xx = x  + l * cos(dt->Tvec.ang);
		float yy = y + l * sin(dt->Tvec.ang);
		mlx_pixel_put(dt->Tmlx.mlx, dt->Tmlx.win, xx, yy, 0x000000);
	}
}

void drawPlayer(t_data *dt, t_img *pl ,float x, float y)
{
	mlx_put_image_to_window(dt->Tmlx.mlx, dt->Tmlx.win, pl->img, x, y);
	drawDiagonal(dt, x, y);
}

int drawMap2D(t_data *dt)
{
	for (size_t i = 0; i < 8; i++)
	{
		for (size_t j = 0; j < 8; j++)
		{
			int x = j * 128;
			int y = i * 96;
			if (basicMap[i][j] == '1')
				mlx_put_image_to_window(dt->Tmlx.mlx, dt->Tmlx.win, dt->Timgs.img_g.img, x, y);
			else
				mlx_put_image_to_window(dt->Tmlx.mlx, dt->Tmlx.win, dt->Timgs.img_w.img, x, y);
			drawPlayer(dt, &dt->Timgs.img_p, dt->Tvec.x, dt->Tvec.y);
		}
	}
	return (0);
}

int keyAction(int key, t_data *dt)
{
	t_vector *p = &dt->Tvec;

	if (key == KEY_W)
	{
		p->x += p->dx;
		p->y += p->dy;
	}
	else if (key == KEY_S)
	{
		p->x -= p->dx;
		p->y -= p->dy;
	}
	else if (key == KEY_A)
	{
		p->ang -= 0.1;
		if (p->ang < 0)
			p->ang += 2 * M_PI;
		p->dx = cos(p->ang) * 5;
		p->dy = sin(p->ang) * 5;
	}
	else if (key == KEY_D)
	{
		p->ang += 0.1;
		if (p->ang > 2 * M_PI)
			p->ang -= 2 * M_PI;
		p->dx = cos(p->ang) * 5;
		p->dy = sin(p->ang) * 5;
	}
	return (0);
}

int	main(int argc, char const *argv[])
{
	(void)argc;
	(void)argv;
	t_data	*dt;

	dt = (t_data *)malloc(sizeof(t_data));
	if (dt == NULL)
		ft_error(NULL);
	init(dt);
	mlx_loop_hook(dt->Tmlx.mlx, drawMap2D, dt);
	mlx_hook(dt->Tmlx.win, 2, 1L << 0, keyAction, dt);
	mlx_hook(dt->Tmlx.win, 17, 1L << 2, destroyWindow, dt);
	mlx_loop(dt->Tmlx.mlx);
	return 0;
}
