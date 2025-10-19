/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sphere.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: musisman <musisman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/19 16:17:28 by musisman          #+#    #+#             */
/*   Updated: 2025/10/19 16:17:28 by musisman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minirt.h"

static double	calculate_sphere_discriminant(t_sphere *sphere,
	const t_ray *r, t_vector3 *oc)
{
	double	a;
	double	half_b;
	double	c;
	double	radius;

	radius = sphere->diameter / 2.0;
	*oc = vec_sub(r->origin, sphere->pos);
	a = vec_dot(r->direction, r->direction);
	half_b = vec_dot(*oc, r->direction);
	c = vec_dot(*oc, *oc) - radius * radius;
	return (half_b * half_b - a * c);
}

bool	hit_sphere(t_object *object, t_hit_status *params)
{
	t_sphere	*sphere;
	t_vector3	oc;
	double		discriminant;
	double		root;
	double		sqrtd;

	sphere = (t_sphere *)object->data;
	discriminant = calculate_sphere_discriminant(sphere, params->ray, &oc);
	if (discriminant < 0)
		return (false);
	sqrtd = sqrt(discriminant);
	root = (-vec_dot(oc, params->ray->direction) - sqrtd)
		/ vec_dot(params->ray->direction, params->ray->direction);
	if (root < params->t_min || params->t_max < root)
	{
		root = (-vec_dot(oc, params->ray->direction) + sqrtd)
			/ vec_dot(params->ray->direction, params->ray->direction);
		if (root < params->t_min || params->t_max < root)
			return (false);
	}
	params->rec->t = root;
	params->rec->p = ray_at(*(params->ray), params->rec->t);
	params->rec->normal = vec_scale(vec_sub(params->rec->p, sphere->pos),
			1.0 / (sphere->diameter / 2.0));
	return (true);
}

t_object	*new_sphere(t_vector3 center, double diameter)
{
	t_object	*obj;
	t_sphere	*sphere_data;

	obj = ft_malloc(sizeof(t_object));
	sphere_data = ft_malloc(sizeof(t_sphere));
	sphere_data->pos = center;
	sphere_data->diameter = diameter;
	obj->type = SPHERE;
	obj->data = sphere_data;
	obj->hit = &hit_sphere;
	return (obj);
}
