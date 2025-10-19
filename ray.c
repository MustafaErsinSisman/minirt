/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: musisman <musisman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/19 16:19:23 by musisman          #+#    #+#             */
/*   Updated: 2025/10/19 16:19:23 by musisman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_ray	new_ray(t_vector3 origin, t_vector3 direction)
{
	t_ray	r;

	r.origin = origin;
	r.direction = direction;
	return (r);
}

t_vector3	ray_at(t_ray r, double t)
{
	return (vec_sum(r.origin, vec_scale(r.direction, t)));
}

unsigned int	color(int r, int g, int b)
{
	return ((r << 16) | (g << 8) | b);
}

static unsigned int	get_background_color(const t_ray *ray)
{
	t_vector3	unit_direction;
	double		a;
	double		r;
	double		g;
	double		b;

	unit_direction = vec_normalize(ray->direction);
	a = 0.5 * (unit_direction.y + 1.0);
	r = (1.0 - a) * 1.0 + a * 0.5;
	g = (1.0 - a) * 1.0 + a * 0.7;
	b = (1.0 - a) * 1.0 + a * 1.0;
	return (color((int)(255.999 * r),
		(int)(255.999 * g), (int)(255.999 * b)));
}

unsigned int	ray_color(t_ray ray, t_list *world)
{
	t_hit_record	rec;
	t_hit_status	status;
	double			r;
	double			g;
	double			b;

	status.ray = &ray;
	status.t_min = 0.001;
	status.t_max = INFINITY;
	status.rec = &rec;
	if (hit_world(world, &status))
	{
		r = 0.5 * (rec.normal.x + 1.0);
		g = 0.5 * (rec.normal.y + 1.0);
		b = 0.5 * (rec.normal.z + 1.0);
		return (color((int)(255.999 * r),
			(int)(255.999 * g), (int)(255.999 * b)));
	}
	return (get_background_color(&ray));
}
