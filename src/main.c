/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shogura <shogura@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/09 20:25:04 by shogura           #+#    #+#             */
/*   Updated: 2022/09/13 16:23:11 by shogura          ###   ########.fr       */
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

int	keyAction(t_data *dt){
	(void)dt;
	return (0);
}

void drawPlayer(t_data *dt, int x, int y)
{
	for (size_t i = 0; i < 10; i++)
		for (size_t j = 0; j < 10; j++)
			mlx_pixel_put(dt->Tmlx.mlx, dt->Tmlx.win, x + j, y + i, 0xFFFF00);
}

int drawMap2D(t_data *dt)
{
	(void)dt;
	for (size_t i = 0; i < 8; i++)
	{
		for (size_t j = 0; j < 8; j++)
		{
			int x = j * 128;
			int y = i * 96;
			if (basicMap[i][j] == '1')
				mlx_put_image_to_window(dt->Tmlx.mlx, dt->Tmlx.win, dt->Timgs.img1.img, x, y);
			else
				mlx_put_image_to_window(dt->Tmlx.mlx, dt->Tmlx.win, dt->Timgs.img2.img, x, y);
		}
	}
	drawPlayer(dt, dt->Tvec.x, dt->Tvec.y);
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
	drawMap2D(dt);
	mlx_loop_hook(dt->Tmlx.mlx, drawMap2D, dt);
	mlx_hook(dt->Tmlx.win, 2, 1L << 0, keyAction, dt);
	mlx_hook(dt->Tmlx.win, 17, 1L << 2, destroyWindow, dt);
	mlx_loop(dt->Tmlx.mlx);
	return 0;
}
