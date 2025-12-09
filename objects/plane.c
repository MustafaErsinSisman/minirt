/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   plane.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: musisman <musisman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/02 16:35:36 by musisman          #+#    #+#             */
/*   Updated: 2025/12/02 16:35:36 by musisman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minirt.h"

static void	set_plane_normal(t_hit_record *rec, const t_ray *r,
	t_vector3 plane_normal)
{
	if (vec_dot(r->direction, plane_normal) > 0)
	{
		rec->front_face = false;
		rec->normal = vec_scale(plane_normal, -1);
	}
	else
	{
		rec->front_face = true;
		rec->normal = plane_normal;
	}
}

bool	hit_plane(t_object *object, t_hit_status *status)
{
	t_plane		*plane;
	double		denominator;
	double		numerator;
	double		t;
	t_vector3	p0_minus_origin;

	plane = (t_plane *)object->data;
	denominator = vec_dot(status->ray->direction, plane->normal);
	if (fabs(denominator) < 1e-6)
		return (false);
	p0_minus_origin = vec_sub(plane->pos, status->ray->origin);
	numerator = vec_dot(p0_minus_origin, plane->normal);
	t = numerator / denominator;
	if (t < status->t_min || t > status->t_max)
		return (false);
	status->rec->t = t;
	status->rec->p = ray_at(*(status->ray), t);
	set_plane_normal(status->rec, status->ray, plane->normal);
	status->rec->color = plane->rgb;
	return (true);
}

t_object	*new_plane(t_vector3 pos, t_vector3 normal, t_vector3 rgb)
{
	t_object	*obj;
	t_plane		*plane_data;

	obj = ft_malloc(sizeof(t_object));
	plane_data = ft_malloc(sizeof(t_plane));
	plane_data->pos = pos;
	plane_data->normal = vec_normalize(normal);
	plane_data->rgb = rgb;
	obj->type = PLANE;
	obj->data = plane_data;
	obj->hit = &hit_plane;
	return (obj);
}
