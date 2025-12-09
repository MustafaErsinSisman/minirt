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

static void	set_face_normal(t_hit_record *rec, const t_ray *r,
	t_vector3 outward_normal)
{
	if (vec_dot(r->direction, outward_normal) < 0)
	{
		rec->front_face = true;
		rec->normal = outward_normal;
	}
	else
	{
		rec->front_face = false;
		rec->normal = vec_scale(outward_normal, -1);
	}
}

static double	calculate_sphere_discriminant(t_sphere *sphere,
	const t_ray *r, t_vector3 *oc)
{
	double	a;
	double	half_b;
	double	c;

	*oc = vec_sub(sphere->pos, r->origin);
	a = vec_dot(r->direction, r->direction);
	half_b = vec_dot(*oc, r->direction);
	c = vec_dot(*oc, *oc) - pow(sphere->radius, 2);
	return (pow(half_b, 2) - a * c);
}

static void	fill_hit_record(t_hit_status *status, t_sphere *sphere, double root)
{
	t_vector3	outward_normal;

	status->rec->t = root;
	status->rec->p = ray_at(*(status->ray), status->rec->t);
	outward_normal = vec_scale(vec_sub(status->rec->p, sphere->pos),
			1.0 / sphere->radius);
	set_face_normal(status->rec, status->ray, outward_normal);
	status->rec->color = sphere->rgb;
}

bool	hit_sphere(t_object *object, t_hit_status *status)
{
	t_sphere	*sphere;
	t_vector3	oc;
	double		discriminant;
	double		root;
	double		sqrtd;

	sphere = (t_sphere *)object->data;
	discriminant = calculate_sphere_discriminant(sphere, status->ray, &oc);
	if (discriminant < 0)
		return (false);
	sqrtd = sqrt(discriminant);
	root = (vec_dot(oc, status->ray->direction) - sqrtd)
		/ vec_dot(status->ray->direction, status->ray->direction);
	if (root < status->t_min || root > status->t_max)
	{
		root = (vec_dot(oc, status->ray->direction) + sqrtd)
			/ vec_dot(status->ray->direction, status->ray->direction);
		if (root < status->t_min || root > status->t_max)
			return (false);
	}
	fill_hit_record(status, sphere, root);
	return (true);
}

t_object	*new_sphere(t_vector3 center, double radius, t_vector3 rgb)
{
	t_object	*obj;
	t_sphere	*sphere_data;

	obj = ft_malloc(sizeof(t_object));
	sphere_data = ft_malloc(sizeof(t_sphere));
	sphere_data->pos = center;
	sphere_data->diameter = radius * 2.0;
	sphere_data->radius = radius;
	sphere_data->rgb = rgb;
	obj->type = SPHERE;
	obj->data = sphere_data;
	obj->hit = &hit_sphere;
	return (obj);
}
