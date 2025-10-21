/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: musisman <musisman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/19 16:05:56 by musisman          #+#    #+#             */
/*   Updated: 2025/10/19 16:05:56 by musisman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_list	*world_objects(void)
{
	t_list	*world;

	world = NULL;
	ft_lstadd_back(&world, ft_lstnew(new_sphere(new_vector(0, 0, -1), 1.0)));
	return (world);
}

static bool	mlx_process(t_list *world)
{
	t_vars	vars;

	vars.mlx = mlx_init();
	if (!vars.mlx)
		return (false);
	vars.win = mlx_new_window(vars.mlx, WIDTH, HEIGHT, "miniRT");
	if (!vars.win)
		return (false);
	vars.img = mlx_new_image(vars.mlx, WIDTH, HEIGHT);
	if (!vars.img)
		return (mlx_destroy_window(vars.mlx, vars.win), false);
	vars.addr = mlx_get_data_addr(vars.img, &vars.bpp,
			&vars.line_len, &vars.endian);
	render_scene(&vars, world);
	mlx_put_image_to_window(vars.mlx, vars.win, vars.img, 0, 0);
	mlx_key_hook(vars.win, key_hook, &vars);
	mlx_hook(vars.win, 17, 0, exit_func, &vars);
	mlx_loop(vars.mlx);
	return (true);
}

int	main(void)
{
	if (!mlx_process(world_objects()))
		return (ft_free(), 1);
	ft_free();
	return (0);
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
	if (keycode == 65307) // ESC tuşu
		exit_func(vars);
	return (0);
}
