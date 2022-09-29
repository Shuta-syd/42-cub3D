/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shogura <shogura@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/09 22:34:35 by shogura           #+#    #+#             */
/*   Updated: 2022/09/29 17:49:51 by shogura          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include <stdio.h>
# include <stdlib.h>
# include <stdbool.h>
# include <libft.h>
# include <fcntl.h>
# include <limits.h>
# include <math.h>
# include <mlx.h>
# include "struct.h"
# include "function.h"

/**
 * @ window size & map info
 */
# define TILESIZE 64
# define MINIMAP_SCALE 0.2

/**
 * @ map info
 */
# define POS 8;
# define NONE 9;

/**
 * @ angle of view & ray info
 */
# define FOV_ANGLE (60 * M_PI / 180)
# define DIST_PROJ_PLANE ((g_window_w / 2) / tan(FOV_ANGLE / 2))

/**
 * @keycode (JIS)
 */
# define UP 119
# define DOWN 115
# define LEFT 97
# define RIGHT 100
# define ESC 65307
# define ARROW_L 65361
# define ARROW_R 65363

/**
 * @ message
 */
# define ERROR "[ERROR] something wrong"

/**
 * @ images info
 */
# define NORTH 0
# define SOUTH 1
# define WEST 2
# define EAST 3

int	g_window_w;
int	g_window_h;
int	g_num_rays;
#endif
