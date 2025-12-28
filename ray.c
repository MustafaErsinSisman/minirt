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

static t_vector3	sample_square(unsigned int *seed)
{
	return (new_vector(ft_random_double(seed) - 0.5, ft_random_double(seed) - 0.5, 0));
}

t_ray	get_ray(t_data *data, int i, int j, unsigned int *seed)
{
	t_vector3	offset;
	t_vector3	pixel_sample;
	t_vector3	ray_origin;
	t_vector3	ray_direction;

	offset = sample_square(seed);
	pixel_sample = vec_sum(data->c_stat.pixel00_loc,
			vec_sum(vec_scale(data->c_stat.delta_u, i + offset.x),
				vec_scale(data->c_stat.delta_v, j + offset.y)));
	ray_origin = data->camera.pos;
	ray_direction = vec_sub(pixel_sample, ray_origin);
	return (new_ray(ray_origin, ray_direction));
}
