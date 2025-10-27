/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: musisman <musisman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/19 16:48:50 by musisman          #+#    #+#             */
/*   Updated: 2025/10/19 16:48:50 by musisman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static t_viewport	setup_viewport(void) // TODO world structını al, t_objects_list structı olacak yani
{
	t_viewport	vp;
	double		focal_length;
	t_vector3	view_u;
	t_vector3	view_v;
	t_vector3	upper_left;

	focal_length = 1.0;
	vp.camera_center = new_vector(0, 0, 0); // TODO parserdan gelecek
	view_u = new_vector(2.0 * (WIDTH / HEIGHT), 0, 0);
	view_v = new_vector(0, -2.0, 0);
	vp.delta_u = vec_scale(view_u, 1.0 / WIDTH);
	vp.delta_v = vec_scale(view_v, 1.0 / HEIGHT);
	upper_left = vec_sub(vp.camera_center, new_vector(0, 0, focal_length));
	upper_left = vec_sub(upper_left, vec_scale(view_u, 0.5));
	upper_left = vec_sub(upper_left, vec_scale(view_v, 0.5));
	vp.pixel00_loc = vec_sum(upper_left,
			vec_scale(vec_sum(vp.delta_u, vp.delta_v), 0.5));
	return (vp);
}

void	render_scene(t_vars *vars, t_list *world)
{
	int			x;
	int			y;
	t_viewport	vp;
	t_vector3	pixel_center;
	t_ray		r;

	vp = setup_viewport();
	y = 0;
	while (y < HEIGHT)
	{
		x = 0;
		while (x < WIDTH)
		{
			pixel_center = vec_sum(vp.pixel00_loc, vec_sum(vec_scale(vp.delta_u,
							x), vec_scale(vp.delta_v, y)));
			r.origin = vp.camera_center;
			r.direction = vec_sub(pixel_center, vp.camera_center);
			*(unsigned int *)(vars->addr + y * vars->size_line + x
					* (vars->bpp / 8)) = ray_color(r, world);
			x++;
		}
		y++;
	}
}
