/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: musisman <musisman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/02 16:35:32 by musisman          #+#    #+#             */
/*   Updated: 2025/12/02 16:35:32 by musisman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minirt.h"

bool	hit_cylinder(t_object *obj, t_hit_status *status)
{
	t_cylinder	*cy;
	t_cy_vars	v;

	cy = (t_cylinder *)obj->data;
	if (!solve_cylinder_quadratic(cy, status->ray, v.t))
		return (false);
	v.t_final = status->t_max;
	v.type = 0;
	check_body_height(cy, status, &v);
	check_caps(cy, status, &v);
	if (v.type == 0)
		return (false);
	status->rec->t = v.t_final;
	status->rec->p = ray_at(*(status->ray), v.t_final);
	if (v.type == 1)
		status->rec->normal = get_cylinder_normal(cy, status->rec->p);
	else if (v.type == 2)
		status->rec->normal = cy->normal;
	else
		status->rec->normal = vec_scale(cy->normal, -1);
	if (vec_dot(status->ray->direction, status->rec->normal) > 0)
		status->rec->normal = vec_scale(status->rec->normal, -1);
	status->rec->color = cy->rgb;
	return (true);
}

t_object	*new_cylinder(t_vector3 pos, t_vector3 normal,
			double diameter_height[2], t_vector3 rgb)
{
	t_object	*obj;
	t_cylinder	*cy;

	obj = ft_malloc(sizeof(t_object));
	cy = ft_malloc(sizeof(t_cylinder));
	cy->pos = pos;
	cy->normal = vec_normalize(normal);
	cy->diameter = diameter_height[0];
	cy->radius = diameter_height[0] / 2.0;
	cy->height = diameter_height[1];
	cy->rgb = rgb;
	obj->type = CYLINDER;
	obj->data = cy;
	obj->hit = &hit_cylinder;
	return (obj);
}
