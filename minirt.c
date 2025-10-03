/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: musisman <musisman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/07 16:01:24 by musisman          #+#    #+#             */
/*   Updated: 2025/10/03 14:51:53 by musisman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

// #define HEIGHT get_height(WIDTH, ASPECT_RATIO)

// static inline int get_height(int width, double aspect_ratio) // küçük bir değer verilirse diye
// {
//     int h = (int)(width / aspect_ratio);
//     if (h < 1)
//         return 1;
//     return h;
// }

#define WIDTH 400.0
#define ASPECT_RATIO (16.0 / 9.0)
#define HEIGHT (WIDTH / ASPECT_RATIO)



typedef struct s_vars
{
    void *mlx;
    void *win;
    void *img;
    char *addr;
} t_vars;

int exit_func(t_vars *vars)
{
	mlx_destroy_image(vars->mlx, vars->img);
	mlx_destroy_window(vars->mlx, vars->win);
	mlx_destroy_display(vars->mlx);
	free(vars->mlx);
	ft_free();
	exit(0);
}

int key_hook(int keycode, t_vars *vars)
{
	if (keycode == 65307)  // ESC
		exit_func(vars);
	return (0);
}

unsigned int color(int r, int g, int b)
{
	unsigned int	hex_color;

	hex_color = (r << 16) | (g << 8) | b;
	return hex_color;
}

t_vector3 *ray_calculate(t_vector3 *orig, t_vector3 *dir, double t)
{
	return (vec_sum(orig, vec_scale(dir, t)));
}

t_vector3 *ray_color(t_vector3 *ray)
{
	ray->x = (double)color(255, 0, 0); // red
	ray->y = (double)color(0, 255, 0); // green
	ray->z = (double)color(0, 0, 255); // blue

	return ray;
}

int main(void)
{
	t_vars vars;
	int bpp;
	int line_len;
	int endian;

	vars.mlx = mlx_init();
	vars.win = mlx_new_window(vars.mlx, WIDTH, HEIGHT, "miniRT");
	vars.img = mlx_new_image(vars.mlx, WIDTH, HEIGHT);
	vars.addr = mlx_get_data_addr(vars.img, &bpp, &line_len, &endian);


	float focal_lentgh = 1.0;
	float view_height = 2.0;
	float view_witdh = view_height * (WIDTH / HEIGHT);

	t_vector3 *camera_center = new_vector(0, 0, 0);
	if (!camera_center)// malloc error;
		ft_exit();

	t_vector3 *view_u = new_vector(view_witdh, 0, 0);
	if (!view_u)// malloc error;
		ft_exit();

	t_vector3 *view_v = new_vector(0, -view_height, 0);
	if (!view_v)// malloc error;
		ft_exit();

	t_vector3 *delta_view_u = vec_scale(view_u, 1.0 / WIDTH);
	t_vector3 *delta_view_v = vec_scale(view_v, 1.0 / HEIGHT);


	t_vector3 *view_upper_left = vec_sub(vec_sub(vec_sub(camera_center, new_vector(0, 0, focal_lentgh)), vec_scale(view_u, 1.0 / 2.0)), vec_scale(view_v, 1.0 / 2.0));
	t_vector3 *pixel00_loc = vec_sum(view_upper_left, vec_scale(vec_sum(delta_view_u, delta_view_v), 0.5));
	t_vector3 *pixel_color = new_vector(0, 0, 0);

	int x;
	int y;
	for(y = 0; y < HEIGHT; y++)
	{
		for (x = 0; x < WIDTH; x++)
		{
			t_vector3 *pixel_center = vec_sum(vec_sum(pixel00_loc, vec_scale(delta_view_u, x)), vec_scale(delta_view_v, y));
			t_vector3 *ray_direction = vec_sub(pixel_center, camera_center);

			t_vector3 *r = ray_calculate(camera_center, ray_direction, 10);
			pixel_color = ray_color(r);
			// printf("color: %f %f %f\n", pixel_color->x, pixel_color->y, pixel_color->z);
		}
	}

	for (y = 0; y < HEIGHT; y++)
    	{
		for (x = 0; x < WIDTH; x++)
    		{
    	        	if (y < HEIGHT / 2)
    	        	{
    	        	    if (x < WIDTH / 3)
					*(unsigned int *)(vars.addr + y * line_len + x * (bpp / 8)) = (unsigned int)pixel_color->x;
    	        	    else if (x < 2 * WIDTH / 3)
					*(unsigned int *)(vars.addr + y * line_len + x * (bpp / 8)) = (unsigned int)pixel_color->y;
    	        	    else
					*(unsigned int *)(vars.addr + y * line_len + x * (bpp / 8)) = (unsigned int)pixel_color->z;
    	        	}
    	        	else
    	        	{
    	        	    if (x < WIDTH / 3)
					*(unsigned int *)(vars.addr + y * line_len + x * (bpp / 8)) =  (unsigned int)pixel_color->x;
    	        	    else if (x < 2 * WIDTH / 3)
					*(unsigned int *)(vars.addr + y * line_len + x * (bpp / 8)) =  (unsigned int)pixel_color->x;
    	        	    else
					*(unsigned int *)(vars.addr + y * line_len + x * (bpp / 8)) =  (unsigned int)pixel_color->x;
    	        	}
    		}
    	}

	mlx_put_image_to_window(vars.mlx, vars.win, vars.img, 0, 0);
	mlx_key_hook(vars.win, key_hook, &vars);
	mlx_hook(vars.win, 17, 0, exit_func, &vars); // çarpıya tıklayınca
	mlx_loop(vars.mlx);
	ft_free(); // unutma;
	return (0);
}
