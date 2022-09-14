/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shogura <shogura@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/09 22:34:35 by shogura           #+#    #+#             */
/*   Updated: 2022/09/14 22:15:32 by shogura          ###   ########.fr       */
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
	t_vec	pos;
	t_vec	dir;
	t_vec	pl;
	t_vec	side;
	t_vec	dl;
	t_vec	ray;
	double	fov;
} t_player;

typedef struct s_data
{
	t_mlx		Tmlx;
	t_map		Tmap;
	t_player	P;
} t_data;

#endif
