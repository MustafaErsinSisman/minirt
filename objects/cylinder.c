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

static t_vector3	get_cylinder_normal(t_cylinder *cy, t_vector3 p)
{
	t_vector3	cp;      // Merkezden P'ye vektör
	t_vector3	proj;    // İzdüşüm vektörü
	double		t;       // İzdüşüm mesafesi

	cp = vec_sub(p, cy->pos);
	t = vec_dot(cp, cy->normal);
	proj = vec_scale(cy->normal, t);
	return (vec_normalize(vec_sub(cp, proj)));
}

static bool	solve_cylinder_quadratic(t_cylinder *cy, const t_ray *r, double *t)
{
	t_vector3	oc;
	double		a;
	double		b;
	double		c;
	double		discriminant;
	
	// Matematiksel formül: (axB)^2 ... yerine daha optimize bir yöntem:
	oc = vec_sub(r->origin, cy->pos);
	// a = dot(D, D) - dot(D, normal)^2
	a = vec_dot(r->direction, r->direction) 
		- pow(vec_dot(r->direction, cy->normal), 2);
	// b = 2 * (dot(D, oc) - dot(D, normal) * dot(oc, normal))
	b = 2 * (vec_dot(r->direction, oc) 
		- (vec_dot(r->direction, cy->normal) * vec_dot(oc, cy->normal)));
	// c = dot(oc, oc) - dot(oc, normal)^2 - r^2
	c = vec_dot(oc, oc) 
		- pow(vec_dot(oc, cy->normal), 2) - (cy->radius * cy->radius);
	discriminant = b * b - 4 * a * c;
	if (discriminant < 0)
		return (false);
	// İki kökü bul (Giriş ve Çıkış noktaları)
	t[0] = (-b - sqrt(discriminant)) / (2 * a);
	t[1] = (-b + sqrt(discriminant)) / (2 * a);
	return (true);
}

static bool	check_height(t_cylinder *cy, const t_ray *r, double t)
{
	t_vector3	p;
	double		proj_len;

	// P = O + tD
	p = ray_at(*r, t);
	// İzdüşüm boyu = dot(P - pos, normal)
	proj_len = vec_dot(vec_sub(p, cy->pos), cy->normal);
	// Eğer izdüşüm -h/2 ile +h/2 arasındaysa geçerlidir.
	if (proj_len >= -(cy->height / 2.0) && proj_len <= (cy->height / 2.0))
		return (true);
	return (false);
}

bool	hit_cylinder(t_object *obj, t_hit_status *status)
{
	t_cylinder	*cy;
	t_vector3	outward_normal;
	double		t[2]; // t[0] = yakın kök, t[1] = uzak kök
	double		final_t;
	
	cy = (t_cylinder *)obj->data;
	if (!solve_cylinder_quadratic(cy, status->ray, t))
		return (false);
	final_t = -1.0;
	if (t[0] > status->t_min && t[0] < status->t_max && check_height(cy, status->ray, t[0]))
		final_t = t[0];
	else if (t[1] > status->t_min && t[1] < status->t_max && check_height(cy, status->ray, t[1]))
		final_t = t[1];
	if (final_t < 0) // İki kök de geçersizse
		return (false);
	status->rec->t = final_t;
	status->rec->p = ray_at(*(status->ray), final_t);
	outward_normal = get_cylinder_normal(cy, status->rec->p);
	if (vec_dot(status->ray->direction, outward_normal) > 0)
		status->rec->normal = vec_scale(outward_normal, -1);
	else
		status->rec->normal = outward_normal;
	return (true);
}

t_object	*new_cylinder(t_vector3 pos, t_vector3 normal, double diameter_height[2], t_vector3 rgb)
{
	t_object	*obj;
	t_cylinder	*cy;

	obj = ft_malloc(sizeof(t_object));
	cy = ft_malloc(sizeof(t_cylinder));
	cy->pos = pos;
	cy->normal = vec_normalize(normal); // Ekseni her zaman normalize et!
	cy->diameter = diameter_height[0];
	cy->radius = diameter_height[0] / 2.0;
	cy->height = diameter_height[1];
	cy->rgb = rgb;
	obj->type = CYLINDER;
	obj->data = cy;
	obj->hit = &hit_cylinder;
	return (obj);
}
