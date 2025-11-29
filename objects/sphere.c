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
	t_vector3 outward_normal) // * yüzey normalini ayarlama fonksiyonu bunun sebebi ise ışının yüzeye dışarıdan mı yoksa içeriden mi çarptığını bilmemiz gerekiyor çünkü normal vektörü her zaman yüzeyin dışarısına doğru olmalı
{
	if (vec_dot(r->direction, outward_normal) < 0) // * ışın ile normalin noktasal çarpımı negatif ise yüzeye dışarıdan çarpmıştır
	{
		rec->front_face = true;
		rec->normal = outward_normal; // * normal olduğu gibi atandı
	}
	else // * ışın ile normalin noktasal çarpımı pozitif ise yüzeye içeriden çarpmıştır
	{
		rec->front_face = false;
		rec->normal = vec_scale(outward_normal, -1); // * normal ters çevrildi
	}
}

static double	calculate_sphere_discriminant(t_sphere *sphere,
	const t_ray *r, t_vector3 *oc)
{
	double	a; // * direction vektörünün uzunluğunun karesi
	double	half_b; // * oc ile direction vektörünün noktasal çarpımı
	double	c; // * oc vektörünün uzunluğunun karesi eksi yarıçapın karesi

	*oc = vec_sub(sphere->pos, r->origin); // * (C - P)
	a = vec_dot(r->direction, r->direction); // * d.d
	half_b = vec_dot(*oc, r->direction); // * d.(C - P) yani d.oc
	c = vec_dot(*oc, *oc) - pow(sphere->radius, 2); // * (C - P).(C - P) - r^2 yani oc.oc - r^2
	return (pow(half_b, 2) - a * c); // * diskriminant değeri hesaplandı b² - 4ac formülünde 4a kısmı yarıya indirildiği için half_b kullanıldı
}

static void	fill_hit_record(t_hit_status *status, t_sphere *sphere, double root) // * çarpma kaydı dolduruldu
{
	t_vector3	outward_normal;	// * yüzey normali

	status->rec->t = root; // * çarpma noktasının t değeri atandı 
	status->rec->p = ray_at(*(status->ray), status->rec->t); // * çarpma noktası hesaplandı
	outward_normal = vec_scale(vec_sub(status->rec->p, sphere->pos),
			1.0 / sphere->radius); // * yüzey normali hesaplandı (P - C) / r formülü kullanıldı burada P çarpma noktası C küre merkezi r ise yarıçap
	// TODO outward_normal = vec_normalize(vec_sub(status->rec->p, sphere->pos)); // normalizasyon yapmak için bu da kullanılabilir ama yukaridaki daha optimize buradaki ise daha güvenli proje gidişine göre karar verilecek
	set_face_normal(status->rec, status->ray, outward_normal); // * yüzey normali ayarlandı 
}

bool	hit_sphere(t_object *object, t_hit_status *status) // * küre çarpma testi fonksiyonu
{
	t_sphere	*sphere; // * küre nesnesi
	t_vector3	oc; // * ray origin ile küre merkezi arasındaki vektör
	double		discriminant; // * diskriminant değeri bu değer negatif ise çarpma yok pozitif ise çarpma var
	double		root; // * çarpma noktasının t değeri bu değer köklerden biri olacak
	double		sqrtd; // * diskriminantın karekökü bu formülde kullanılıyor -b ± √(b² - 4ac) / 2a formülünde b² - 4ac kısmı diskriminantı temsil eder ve kök kısmında kullanılır

	sphere = (t_sphere *)object->data; // * küre nesnesi alındı
	discriminant = calculate_sphere_discriminant(sphere, status->ray, &oc); // * diskriminant değeri hesaplandı
	if (discriminant < 0)
		return (false);
	sqrtd = sqrt(discriminant); // * diskriminantın karekökü hesaplandı 
	root = (vec_dot(oc, status->ray->direction) - sqrtd)
		/ vec_dot(status->ray->direction, status->ray->direction); // * çarpma noktasının t değeri hesaplandı burada -b - √(b² - 4ac) / 2a formülü kullanıldı ancak 2a kısmı yarıya indirildiği için direkt olarak a ile bölündü
	if (root < status->t_min || root > status->t_max) // * t değeri aralıkta mı kontrolü yapıldı
	{
		root = (vec_dot(oc, status->ray->direction) + sqrtd)
			/ vec_dot(status->ray->direction, status->ray->direction); // * diğer t değeri hesaplandı
		if (root < status->t_min || root > status->t_max) // * t değeri aralıkta mı kontrolü yapıldı
			return (false);
	}
	fill_hit_record(status, sphere, root); // * çarpma kaydı dolduruldu
	return (true);
}

t_object	*new_sphere(t_vector3 center, double radius)
{
	t_object	*obj;
	t_sphere	*sphere_data;

	obj = ft_malloc(sizeof(t_object));
	sphere_data = ft_malloc(sizeof(t_sphere));
	sphere_data->pos = center;
	sphere_data->diameter = radius * 2.0;
	sphere_data->radius = radius;
	obj->type = SPHERE; // BEN BUNU KULLANMAYACAĞIM GALİBA
	obj->data = sphere_data;
	obj->hit = &hit_sphere;
	return (obj);
}
