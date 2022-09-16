/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shogura <shogura@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/09 22:34:35 by shogura           #+#    #+#             */
/*   Updated: 2022/09/16 14:14:24 by shogura          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCT_H
# define STRUCT_H

typedef struct s_mlx
{
	void	*mlx;
	void	*win;
}	t_mlx;

typedef struct s_img
{
	void	*img;
	char	*addr;
	int		bpp;
	int		line_len;
	int		endian;
} t_img;

typedef struct s_imgs
{

} t_imgs;

typedef struct s_map
{
	int x;
	int y;
} t_map;

typedef struct s_vec
{
	double x;
	double y;
} t_vec;

typedef struct s_player
{
	t_vec	pos; // player postion
	t_vec	dir; // player direction
	t_vec	pl; // camera plane
	t_vec	side; // side
	t_vec	dl; //delta
	t_vec	ray; // ray direction
	t_vec	step; // step
	double	fov; // angle
} t_player;

typedef struct s_data
{
	t_mlx		Tmlx;
	t_map		Tmap;
	t_player	P;
	bool hit;
	int side;
	double prepWallDist;
} t_data;

#endif
