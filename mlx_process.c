/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_process.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: musisman <musisman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/10 18:56:45 by musisman          #+#    #+#             */
/*   Updated: 2025/12/10 18:56:45 by musisman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

bool	mlx_process(t_data *data)
{
	t_vars			vars;
	unsigned int	seed;
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	seed = (unsigned int)(tv.tv_sec * 1000000 + tv.tv_usec);
	vars.mlx = mlx_init();
	if (!vars.mlx)
		return (false);
	vars.win = mlx_new_window(vars.mlx, WIDTH, HEIGHT, "miniRT");
	if (!vars.win)
		return (false);
	vars.img = mlx_new_image(vars.mlx, WIDTH, HEIGHT);
	if (!vars.img)
		return (mlx_destroy_window(vars.mlx, vars.win), false);
	vars.addr = mlx_get_data_addr(vars.img, &vars.bpp, &vars.size_line,
			&vars.endian);
	camera_render(data, &vars, &seed);
	mlx_put_image_to_window(vars.mlx, vars.win, vars.img, 0, 0);
	mlx_key_hook(vars.win, key_hook, &vars);
	mlx_hook(vars.win, 17, 0, exit_func, &vars);
	mlx_loop(vars.mlx);
	return (true);
}

int	exit_func(t_vars *vars)
{
	if (vars->img)
		mlx_destroy_image(vars->mlx, vars->img);
	if (vars->win)
		mlx_destroy_window(vars->mlx, vars->win);
	if (vars->mlx)
	{
		mlx_destroy_display(vars->mlx);
		free(vars->mlx);
	}
	ft_free();
	exit(0);
}

int	key_hook(int keycode, t_vars *vars)
{
	if (keycode == 65307)
		exit_func(vars);
	return (0);
}
