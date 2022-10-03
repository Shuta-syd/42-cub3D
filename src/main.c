/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shogura <shogura@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/25 17:31:41 by shogura           #+#    #+#             */
/*   Updated: 2022/10/03 21:22:39 by shogura          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3D.h>

int	main(int ac, char const *av[])
{
	t_data	*dt;

	if (ac != 2)
		return (1);
	dt = ft_calloc(1, sizeof(t_data));
	if (dt == NULL)
		return (ft_error(NULL, M_ERROR));
	parse_map(dt, av[1]);
	init(dt);
	parse_xpm(dt);
	cast_all_rays(dt);
	render(dt);
	mlx_hook(dt->t_mlx.win, 2, 1L << 0, key_action, dt);
	mlx_hook(dt->t_mlx.win, 17, 1L << 2, destroy_window, dt);
	mlx_loop(dt->t_mlx.mlx);
	return (0);
}
