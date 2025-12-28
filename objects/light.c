/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   light.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: musisman <musisman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/02 15:06:29 by musisman          #+#    #+#             */
/*   Updated: 2025/12/02 15:06:29 by musisman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minirt.h"

t_vector3	calculate_diffuse(t_light light, t_hit_record *rec)
{
	t_vector3	light_dir;
	t_vector3	diffuse_color;
	double		diff;

	light_dir = vec_normalize(vec_sub(light.pos, rec->p));
	diff = vec_dot(rec->normal, light_dir);
	if (diff < 0)
		diff = 0;
	diffuse_color = vec_scale(light.rgb, diff * light.range);
	return (diffuse_color);
}

bool	is_in_shadow(t_list *world, t_light light, t_vector3 point)
{
	t_vector3		light_dir;
	double			light_dist;
	t_ray			shadow_ray;
	t_hit_record	rec;
	t_hit_status	status;

	light_dir = vec_sub(light.pos, point);
	light_dist = vec_len(light_dir);
	shadow_ray = new_ray(point, vec_normalize(light_dir));
	status.ray = &shadow_ray;
	status.t_min = 0.001;
	status.t_max = light_dist;
	status.rec = &rec;
	if (hit_world(world, &status))
		return (true);
	return (false);
}
