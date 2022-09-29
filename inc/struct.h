/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shogura <shogura@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/09 22:34:35 by shogura           #+#    #+#             */
/*   Updated: 2022/09/29 14:48:35 by shogura          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCT_H
# define STRUCT_H

#include <cub3D.h>
#define uint unsigned int

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
	float	distanceProjPlane;
	float	correctWallDistance;
	float	projectedWallHeight;
	int		wallStripHeight;
	int		wallTopPixel;
	int		wallBottomPixel;
	int		*texture;
	int		texelColor;
} t_3d;

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
} t_tex;

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
} t_img;

typedef struct s_imgs
{
	t_img	map;
	t_img	P;
	t_img	map3D;
	t_img texture[4];
} t_imgs;

typedef struct s_map
{
	t_list	*list;
	int		**content;
	int		row;
	int		col;
	char	*filepath[4];
	int		floor;
	int		ceiling;
} t_map;

typedef struct s_player
{
	float	x;
	float	y;
	float	width;
	float	height;
	int		turnDirection; // -1 for left, +1 for right
	int		walkDirection; // -1 for back, +1 for front
	float	rotationAngle;
	float	walkSpeed;
	float	turnSpeed;
} t_player;

typedef struct s_horz
{
	int foundHorzWallHit;
	float horzWallHitX;
	float horzWallHitY;
	float nextHorzTouchX;
	float nextHorzTouchY;
	int horzWallContent;
} t_horz;

typedef struct s_vert
{
	int foundVertWallHit;
	float vertWallHitX;
	float vertWallHitY;
	float nextVertTouchX;
	float nextVertTouchY;
	int vertWallContent;
} t_vert;

typedef struct s_dda
{
	int		isRayFacingUp;
	int		isRayFacingDown;
	int		isRayFacingRight;
	int		isRayFacingLeft;
	float	xIntercept;
	float	yIntercept;
	float	xStep;
	float	yStep;
	t_horz H;
	t_vert V;
} t_dda;

typedef struct s_ray
{
	float	rayAngle;
	float	wallHitX;
	float	wallHitY;
	float	distance;
	int		wasHitVertical;
	int		isRayFacingUp;
	int		isRayFacingDown;
	int		isRayFacingRight;
	int		isRayFacingLeft;
	int		wallHitContent;
} t_ray;

/**
 * @ comprehensive data
 */
typedef struct s_data
{
	t_mlx		Tmlx;
	t_map		Tmap;
	t_imgs		Timg;
	t_ray		R[2500];
	t_player	P;
	t_tex		tex[4];
} t_data;

#endif
