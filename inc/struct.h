/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shogura <shogura@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/09 22:34:35 by shogura           #+#    #+#             */
/*   Updated: 2022/09/14 20:43:44 by shogura          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCT_H
# define STRUCT_H

typedef struct s_vector
{
	float	x;
	float	y;
	float dx;
	float dy;
	float ang;
	float l;
} t_vector;

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
	t_img	img_g;
	t_img	img_w;
	t_img	img_p;
} t_imgs;

typedef struct s_vec
{
	int x;
	int y;
} t_vec;

typedef struct s_map
{
	char	**map;
	int		row;
	int		col;
} t_map;

typedef struct s_data
{
	t_mlx	Tmlx;
	t_imgs	Timgs;
	t_map	Tmap;
} t_data;

#endif
