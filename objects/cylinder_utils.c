/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: musisman <musisman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/02 18:35:28 by musisman          #+#    #+#             */
/*   Updated: 2025/12/02 18:35:28 by musisman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minirt.h"

bool	solve_cylinder_quadratic(t_cylinder *cy, const t_ray *r, double *t)
{
	t_vector3	oc;
	double		a;
	double		b;
	double		c;
	double		disc;

	oc = vec_sub(r->origin, cy->pos);
	a = vec_dot(r->direction, r->direction)
		- pow(vec_dot(r->direction, cy->normal), 2);
	b = 2 * (vec_dot(r->direction, oc)
			- (vec_dot(r->direction, cy->normal) * vec_dot(oc, cy->normal)));
	c = vec_dot(oc, oc)
		- pow(vec_dot(oc, cy->normal), 2) - (cy->radius * cy->radius);
	disc = b * b - 4 * a * c;
	if (disc < 0)
		return (false);
	t[0] = (-b - sqrt(disc)) / (2 * a);
	t[1] = (-b + sqrt(disc)) / (2 * a);
	return (true);
}

void	check_body_height(t_cylinder *cy, t_hit_status *st, t_cy_vars *v)
{
	t_vector3	p;
	double		h;

	p = ray_at(*(st->ray), v->t[0]);
	h = vec_dot(vec_sub(p, cy->pos), cy->normal);
	if (v->t[0] > st->t_min && v->t[0] < v->t_final
		&& h >= -cy->height / 2 && h <= cy->height / 2)
	{
		v->t_final = v->t[0];
		v->type = 1;
	}
	p = ray_at(*(st->ray), v->t[1]);
	h = vec_dot(vec_sub(p, cy->pos), cy->normal);
	if (v->t[1] > st->t_min && v->t[1] < v->t_final
		&& h >= -cy->height / 2 && h <= cy->height / 2)
	{
		v->t_final = v->t[1];
		v->type = 1;
	}
}

bool	check_cap_intersection(t_cylinder *cy, const t_ray *ray,
	t_vector3 p_cap, double *t)
{
	double		denom;
	double		t_cap;
	t_vector3	v;

	denom = vec_dot(ray->direction, cy->normal);
	if (fabs(denom) < 1e-6)
		return (false);
	t_cap = vec_dot(vec_sub(p_cap, ray->origin), cy->normal) / denom;
	v = vec_sub(ray_at(*ray, t_cap), p_cap);
	if (vec_dot(v, v) <= (cy->radius * cy->radius))
	{
		*t = t_cap;
		return (true);
	}
	return (false);
}

void	check_caps(t_cylinder *cy, t_hit_status *st, t_cy_vars *v)
{
	t_vector3	caps[2];

	caps[0] = vec_sum(cy->pos, vec_scale(cy->normal, cy->height / 2.0));
	caps[1] = vec_sum(cy->pos, vec_scale(cy->normal, -cy->height / 2.0));
	if (check_cap_intersection(cy, st->ray, caps[0], &v->t[0]))
	{
		if (v->t[0] > st->t_min && v->t[0] < v->t_final)
		{
			v->t_final = v->t[0];
			v->type = 2;
		}
	}
	if (check_cap_intersection(cy, st->ray, caps[1], &v->t[1]))
	{
		if (v->t[1] > st->t_min && v->t[1] < v->t_final)
		{
			v->t_final = v->t[1];
			v->type = 3;
		}
	}
}

t_vector3	get_cylinder_normal(t_cylinder *cy, t_vector3 p)
{
	t_vector3	cp;
	t_vector3	proj;
	double		t;

	cp = vec_sub(p, cy->pos);
	t = vec_dot(cp, cy->normal);
	proj = vec_scale(cy->normal, t);
	return (vec_normalize(vec_sub(cp, proj)));
}
