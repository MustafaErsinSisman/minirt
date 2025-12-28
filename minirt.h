/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: musisman <musisman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/07 16:06:18 by musisman          #+#    #+#             */
/*   Updated: 2025/12/28 18:16:19 by musisman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_H
# define MINIRT_H

# include <sys/time.h>

# include "minilibx-linux/mlx.h"
# include "collector/collector.h"
# include "controller/controller.h"

# define WIDTH 800.0
# define HEIGHT 450.0

# ifndef M_PI
#  define M_PI 3.14159265358979323846264338327950288
# endif

static inline double	degrees_to_radians(double degrees)
{
	return (degrees * M_PI / 180.0);
}

static inline double	ft_random_double(unsigned int *seed)
{
	*seed = *seed * 1103515245 + 12345;
	return ((double)(*seed & 0x7FFFFFFF) / 2147483648.0);
}

static inline double	clamp(double x, double min, double max)
{
	if (x < min)
		return (min);
	if (x > max)
		return (max);
	return (x);
}

typedef struct s_vars
{
	void	*mlx;
	void	*win;
	void	*img;
	char	*addr;
	int		bpp;
	int		size_line;
	int		endian;
}	t_vars;

typedef struct s_data
{
	t_ambient		ambient;
	t_camera		camera;
	t_light			light;
	t_cam_status	c_stat;
	t_list			*world;
}	t_data;

bool				mlx_process(t_data *data);
int					exit_func(t_vars *vars);
int					key_hook(int keycode, t_vars *vars);
t_ray				new_ray(t_vector3 origin, t_vector3 direction);
t_vector3			ray_at(t_ray r, double t);
t_ray				get_ray(t_data *data, int i, int j, unsigned int *seed);
unsigned int		color(int r, int g, int b);

#endif
