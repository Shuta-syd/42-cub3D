/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shogura <shogura@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2"0"22/09/"1"0 "1"8:26:59 by shogura           #+#    #+#             */
/*   Updated: 2022/09/12 17:42:14 by shogura          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3D.h>

#define GRAY  "asset/gray.xpm"
#define WHITE  "asset/white.xpm"

void my_mlx_pixel_put(t_img *img, int x, int y, int color);

void init_mlx(t_data *dt)
{
	dt->Tmlx.mlx = mlx_init();
	dt->Tmlx.win = mlx_new_window(dt->Tmlx.mlx, WIN_W, WIN_H, "cub3D");
}

void init_all_images(t_data *dt, t_img *img, void *mlx, char *filepath)
{
	(void)dt;
	int size = 100;
	img->img = mlx_xpm_file_to_image(mlx, filepath, &size, &size);
	img->addr = mlx_get_data_addr(img->img, &img->bpp, &img->line_len, &img->endian);
}

void initImage(t_data *dt)
{
	init_all_images(dt, &dt->Timgs.img_g, dt->Tmlx.mlx, GRAY);
	init_all_images(dt, &dt->Timgs.img_w, dt->Tmlx.mlx, WHITE);

}

void init(t_data *dt)
{
	init_mlx(dt);
}
