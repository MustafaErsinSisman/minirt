/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yozlu <yozlu@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/07 16:06:18 by musisman          #+#    #+#             */
/*   Updated: 2025/10/24 16:00:19 by yozlu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_H
# define MINIRT_H

# include "minilibx-linux/mlx.h"
# include "collector/collector.h"
# include "controller/controller.h"

# define WIDTH 1920.0
# define HEIGHT 1080.0

typedef struct s_vars
{
	void	*mlx;
	void	*win;
	void	*img;
	char	*addr;
	int		line_len;
	int		bpp;
	int		endian;
}	t_vars;

typedef struct s_viewport
{
	t_vector3	pixel00_loc;
	t_vector3	delta_u;
	t_vector3	delta_v;
	t_vector3	camera_center;
}	t_viewport;

int					exit_func(t_vars *vars);
int					key_hook(int keycode, t_vars *vars);
void				render_scene(t_vars *vars, t_list *world);
t_ray				new_ray(t_vector3 origin, t_vector3 direction);
t_vector3			ray_at(t_ray r, double t);
unsigned int		ray_color(t_ray ray, t_list *world);
unsigned int		color(int r, int g, int b);

#endif
