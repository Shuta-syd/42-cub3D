/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dda.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shogura <shogura@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/14 22:25:07 by shogura           #+#    #+#             */
/*   Updated: 2022/09/14 22:25:41 by shogura          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3D.h>

/**
 * @calculate ray position and direction
 */
void	calcRay(t_data *dt, int x)
{
	double cameraX = 2 * x / (double)screenWidth - 1; // x-coordinate in camera space
	dt->P.ray.x = dt->P.dir.x + dt->P.pl.x * cameraX;
	dt->P.ray.x = dt->P.dir.y + dt->P.pl.y * cameraX;
}

/**
 * @ Digital Differential Analyzer
 */
void	DDA(t_data *dt, int x)
{
	calcRay(dt, x);
}
