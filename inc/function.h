/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   function.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shogura <shogura@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/10 18:27:23 by shogura           #+#    #+#             */
/*   Updated: 2022/09/12 17:24:37 by shogura          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FUNCTION_H
# define FUNCTION_H

#include "struct.h"

void	ft_error(t_data *dt);
void	init(t_data *dt);
int		create_trgb(unsigned char t, unsigned char r, unsigned char g, unsigned char b);

#endif
