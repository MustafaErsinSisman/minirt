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
	double	a; // * direction vektörünün uzunluğunun karesi
	double	half_b; // * oc ile direction vektörünün noktasal çarpımı
	double	c; // * oc vektörünün uzunluğunun karesi eksi yarıçapın karesi
	double	radius; // * küre yarıçapı

	radius = sphere->diameter / 2.0; // * küre yarıçapı hesaplandı
	*oc = vec_sub(sphere->pos, r->origin); // * (C - P)
	a = vec_dot(r->direction, r->direction); // * d.d
	half_b = vec_dot(*oc, r->direction); // * d.(C - P) yani d.oc
	c = vec_dot(*oc, *oc) - pow(radius, 2); // * (C - P).(C - P) - r^2 yani oc.oc - r^2
	return (pow(half_b, 2) - a * c); // * diskriminant değeri hesaplandı b² - 4ac formülünde 4a kısmı yarıya indirildiği için half_b kullanıldı
}

bool	hit_sphere(t_object *object, t_hit_status *params) // * küre çarpma testi fonksiyonu
{
	t_sphere	*sphere; // * küre nesnesi
	t_vector3	oc; // * ray origin ile küre merkezi arasındaki vektör
	double		discriminant; // * diskriminant değeri bu değer negatif ise çarpma yok pozitif ise çarpma var
	double		root; // * çarpma noktasının t değeri bu değer köklerden biri olacak
	double		sqrtd; // * diskriminantın karekökü bu formülde kullanılıyor -b ± √(b² - 4ac) / 2a formülünde b² - 4ac kısmı diskriminantı temsil eder ve kök kısmında kullanılır

	sphere = (t_sphere *)object->data; // * küre nesnesi alındı
	discriminant = calculate_sphere_discriminant(sphere, params->ray, &oc); // * diskriminant değeri hesaplandı
	if (discriminant < 0)
		return (false);
	sqrtd = sqrt(discriminant); // * diskriminantın karekökü hesaplandı 
	root = (vec_dot(oc, params->ray->direction) - sqrtd)
		/ vec_dot(params->ray->direction, params->ray->direction); // * çarpma noktasının t değeri hesaplandı burada -b - √(b² - 4ac) / 2a formülü kullanıldı ancak 2a kısmı yarıya indirildiği için direkt olarak a ile bölündü
	if (root < params->t_min || root > params->t_max) // * t değeri aralıkta mı kontrolü yapıldı
	{
		root = (vec_dot(oc, params->ray->direction) + sqrtd)
			/ vec_dot(params->ray->direction, params->ray->direction); // * diğer t değeri hesaplandı
		if (root < params->t_min || root > params->t_max) // * t değeri aralıkta mı kontrolü yapıldı
			return (false);
	}
	params->rec->t = root; // * çarpma noktasının t değeri kaydedildi
	params->rec->p = ray_at(*(params->ray), params->rec->t); // * çarpma noktası hesaplandı
	params->rec->normal = vec_scale(vec_sub(params->rec->p, sphere->pos),
			1.0 / (sphere->diameter / 2.0)); // * yüzey normali hesaplandı normal vektör birim vektör olmalı bu yüzden çarpma noktasından küre merkezine olan vektörün uzunluğu küre yarıçapına bölündü
	// TODO buraya biraz daha bak
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
