/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   function.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shogura <shogura@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/10 18:27:23 by shogura           #+#    #+#             */
/*   Updated: 2022/09/18 12:37:39 by shogura          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FUNCTION_H
# define FUNCTION_H

#include "struct.h"

/**
 * @ render.c
 */
void renderMap(t_data *dt);

/**
 * @ hook_action.c
 */
int keyAction(int keycode, t_data *dt);
int	destroyWindow(t_data *dt);

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
