/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: musisman <musisman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/07 16:06:18 by musisman          #+#    #+#             */
/*   Updated: 2025/11/26 16:47:02 by musisman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_H
# define MINIRT_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>

# include "minilibx-linux/mlx.h"
# include "objects/objects.h"

# define WIDTH 1920.0
# define HEIGHT 1080.0

typedef struct s_vars
{
	void	*mlx; // * mlx instance
	void	*win; // * window instance
	void	*img; // * image instance
	char	*addr; // * image data address
	int		bpp; // * bits per pixel
	int		size_line; // * size of a line in bytes
	int		endian; // * endianess
}	t_vars;

typedef struct s_viewport
{
	double		focal_length;
	t_vector3	camera_center;
	t_vector3	view_u;
	t_vector3	view_v;
	t_vector3	delta_u;
	t_vector3	delta_v;
	t_vector3	upper_left;
	t_vector3	pixel00_loc;
}	t_viewport;

int					exit_func(t_vars *vars);
int					key_hook(int keycode, t_vars *vars);
void				render_scene(t_vars *vars, t_list *world);
t_ray				new_ray(t_vector3 origin, t_vector3 direction);
t_vector3			ray_at(t_ray r, double t);
unsigned int		ray_color(t_ray ray, t_list *world);
unsigned int		color(int r, int g, int b);

#endif
