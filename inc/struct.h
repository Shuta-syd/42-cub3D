/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shogura <shogura@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/09 22:34:35 by shogura           #+#    #+#             */
/*   Updated: 2022/10/03 21:14:03 by shogura          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCT_H
# define STRUCT_H

# include <cub3D.h>
/**
 * @ struct required for 3d wall
 *
 * distanceProjPlane: distance from player to projection plane
 * correctWallDistance: distance from player to correct wall
 * projectedWallHeight: type of float height of the wall on the window
 * wallStripHeight: type of int height of the wall on the window
 * wallTopPixel:
 * wallBottomPixel:
 */
typedef struct s_3d
{
	float	distance_proj_plane;
	float	correct_wall_distance;
	float	projected_wall_height;
	int		wall_strip_height;
	int		wall_top_pixel;
	int		wall_bottom_pixel;
	int		*texture;
	int		texel_color;
}	t_3d;

typedef struct s_mlx
{
	void	*mlx;
	void	*win;
}	t_mlx;

typedef struct s_tex
{
	int	width;
	int	height;
	int	*data;
}	t_tex;

typedef struct s_img
{
	void	*img;
	char	*addr;
	int		*data;
	int		bpp;
	int		line_len;
	int		endian;
	int		width;
	int		height;
}	t_img;

typedef struct s_imgs
{
	t_img	map;
	t_img	p;
	t_img	map_3d;
	t_img	texture[4];
}	t_imgs;

typedef struct s_map
{
	t_list	*list;
	int		**content;
	int		row;
	int		col;
	char	*filepath[4];
	int		floor;
	int		ceiling;
	int		px;
	int		py;
	int		map_width;
	int		map_height;
}	t_map;

typedef struct s_player
{
	float	x;
	float	y;
	float	width;
	float	height;
	float	turn_direction;
	int		walk_direction;
	float	rotation_angle;
	float	walk_speed;
	float	turn_speed;
}	t_player;

typedef struct s_horz
{
	int		wall_hit;
	int		wall_content;
	float	wall_hit_x;
	float	wall_hit_y;
	float	next_x;
	float	next_y;
}	t_horz;

typedef struct s_vert
{
	int		wall_hit;
	int		wall_content;
	float	wall_hit_x;
	float	wall_hit_y;
	float	next_x;
	float	next_y;
}	t_vert;

typedef struct s_dda
{
	int		map_width;
	int		map_height;
	int		facing_up;
	int		facing_down;
	int		facing_right;
	int		facing_left;
	float	x_intercept;
	float	y_intercept;
	float	x_step;
	float	y_step;
	t_horz	t_h;
	t_vert	t_v;
}	t_dda;

typedef struct s_ray
{
	float	ray_angle;
	float	wall_hit_x;
	float	wall_hit_y;
	float	distance;
	int		was_hit_vertical;
	int		facing_up;
	int		facing_down;
	int		facing_right;
	int		facing_left;
	int		wall_hit_content;
}	t_ray;

/**
 * @ comprehensive data
 */
typedef struct s_data
{
	t_mlx		t_mlx;
	t_map		t_map;
	t_imgs		t_img;
	t_ray		*t_r;
	t_player	t_p;
	t_tex		tex[4];
}	t_data;

#endif
