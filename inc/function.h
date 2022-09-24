/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   function.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shogura <shogura@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/10 18:27:23 by shogura           #+#    #+#             */
/*   Updated: 2022/09/24 18:56:15 by shogura          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FUNCTION_H
# define FUNCTION_H

#include "struct.h"

/**
 * @ render.c
 */
int		render(t_data *dt);
void	renderMap(t_data *dt);
void	renderDrawLine(t_data *dt, float x, float y, float len, float angle, int color);

/**
 * @render3D.c
 */
void	generate3DProjection(t_data *dt);

/**
 * @ ray.c
 */
void	castAllRays(t_data *dt);

/**
 * @ parse.c
 */
void parse(t_data *dt, const char *filepath);
void parseXpm(t_data *dt);

/**
 * @ hook_action.c
 */
int keyAction(int keycode, t_data *dt);
int	destroyWindow(t_data *dt);

/**
 * @ utils.c
 */
bool	mapHasWallAt(float x, float y);
float	distanceBetweenPoints(float x1, float y1, float x2, float y2);

/**
 * @ mlx_utils.c
 */
int		calc_trgb(unsigned char t, unsigned char r, unsigned char g, unsigned char b);
void	my_mlx_pixel_put(t_img *img, int x, int y, int color);

/**
 * @ error.c
 */
void	ft_error(t_data *dt);

/**
 * @ init.c
 */
void	init(t_data *dt);

#endif
