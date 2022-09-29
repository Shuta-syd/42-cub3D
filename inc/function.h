/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   function.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shogura <shogura@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/10 18:27:23 by shogura           #+#    #+#             */
/*   Updated: 2022/09/29 19:35:55 by shogura          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FUNCTION_H
# define FUNCTION_H

/**
 * @ render.c
 */
int		render(t_data *dt);

/**
 * @ render_minimap.c
 */
void	render_rays(t_data *dt);
void	render_player(t_data *dt, float startX, float startY);
void	render_map(t_data *dt);

/**
 * @render3D.c
 */
void	generate3d_projection(t_data *dt);

/**
 * @ ray.c & ray_horz.c & ray_vert.c
 */
void	cast_all_rays(t_data *dt);
void	intersection_horz(t_dda *D, t_data *dt, float rayAngle);
void	intersection_vert(t_dda *D, t_data *dt, float rayAngle);

/**
 * @ ray_horz.c
 */

/**
 * @ parse_map.c & parse_map_utils.c
 */
void	parse_map(t_data *dt, const char *filepath);
void	allocate_map_mem(t_map *map);
void	count_row_col(t_map *map, t_list *lst);
int		count_line(char *line);

/**
 * parse_xpm.c
 */
void	parse_xpm(t_data *dt);

/**
 * @ hook_action.c
 */
int		key_action(int keycode, t_data *dt);
int		destroy_window(t_data *dt);

/**
 * @ utils.c
 */
bool	map_has_wall_at(t_map map, float x, float y);
float	distance_between_points(float x1, float y1, float x2, float y2);

/**
 * @ mlx_utils.c
 */
int		calc_trgb(unsigned char t, unsigned char r,
			unsigned char g, unsigned char b);
void	my_mlx_pixel_put(t_img *img, int x, int y, int color);

/**
 * @ error.c
 */
int		ft_error(t_data *dt, char *msg);

/**
 * @ init.c
 */
void	init(t_data *dt);

#endif
