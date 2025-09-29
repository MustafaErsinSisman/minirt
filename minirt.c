/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: musisman <musisman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/07 16:01:24 by musisman          #+#    #+#             */
/*   Updated: 2025/09/07 19:21:42 by musisman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

#define WIDTH 900
#define HEIGHT 600

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
	exit(0);
}

int key_hook(int keycode, t_vars *vars)
{
	if (keycode == 65307)  // ESC
		exit_func(vars);
	return (0);
}

int main(void)
{
	t_vars vars;
	int bpp, line_len, endian, x, y;

	vars.mlx = mlx_init();
	vars.win = mlx_new_window(vars.mlx, WIDTH, HEIGHT, "miniRT");
	vars.img = mlx_new_image(vars.mlx, WIDTH, HEIGHT);
	vars.addr = mlx_get_data_addr(vars.img, &bpp, &line_len, &endian);

	// kırmızı ekran
	for (y = 0; y < HEIGHT; y++)
    {
		for (x = 0; x < WIDTH; x++)
        {
            if (y < HEIGHT / 2)
            {
                if (x < WIDTH / 3)
			        *(unsigned int *)(vars.addr + y * line_len + x * (bpp / 8)) = 0x00FF0000;
                else if (x < 2 * WIDTH / 3)
			        *(unsigned int *)(vars.addr + y * line_len + x * (bpp / 8)) = 0x0000FF00;
                else
			        *(unsigned int *)(vars.addr + y * line_len + x * (bpp / 8)) = 0x000000FF;
            }
            else
            {
                if (x < WIDTH / 3)
			        *(unsigned int *)(vars.addr + y * line_len + x * (bpp / 8)) = 0x00FFFF00;
                else if (x < 2 * WIDTH / 3)
			        *(unsigned int *)(vars.addr + y * line_len + x * (bpp / 8)) = 0x00FFFFFF;
                else
			        *(unsigned int *)(vars.addr + y * line_len + x * (bpp / 8)) = 0x00000000;
            }
        }
    }

	mlx_put_image_to_window(vars.mlx, vars.win, vars.img, 0, 0);
	mlx_key_hook(vars.win, key_hook, &vars);
	mlx_hook(vars.win, 17, 0, exit_func, &vars); // çarpıya tıklayınca
	mlx_loop(vars.mlx);
	return (0);
}
