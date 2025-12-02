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

// $$t = \frac{(PlanePos - RayOrigin) \cdot PlaneNormal}{RayDirection \cdot PlaneNormal}$$

// Işının yüzeye içeriden mi dışarıdan mı çarptığını belirler
static void	set_plane_normal(t_hit_record *rec, const t_ray *r,
	t_vector3 plane_normal) // * yüzey normalini ayarlama fonksiyonu bunun sebebi ise ışının yüzeye dışarıdan mı yoksa içeriden mi çarptığını bilmemiz gerekiyor çünkü normal vektörü her zaman yüzeyin dışarısına doğru olmalı
{
	if (vec_dot(r->direction, plane_normal) > 0) // * ışın ile normalin noktasal çarpımı pozitif ise yüzeye içeriden çarpmıştır
	{
		rec->front_face = false; // * içeriden çarpma
		rec->normal = vec_scale(plane_normal, -1); // * normal ters çevrildi
	}
	else
	{
		rec->front_face = true; // * dışarıdan çarpma
		rec->normal = plane_normal; // * normal olduğu gibi atandı
	}
}

bool	hit_plane(t_object *object, t_hit_status *status)
{
	t_plane		*plane; // * düzlem nesnesi
	double		denominator; // * ray direction ile düzlem normalinin noktasal çarpımı
	double		numerator; // * (PlanePos - RayOrigin) ile düzlem normalinin noktasal çarpımı
	double		t; // * çarpma t değeri
	t_vector3	p0_minus_origin; // * (PlanePos - RayOrigin)

	plane = (t_plane *)object->data; // * düzlem verisi alındı
	denominator = vec_dot(status->ray->direction, plane->normal); // * ray direction ile düzlem normalinin noktasal çarpımı
	// * Eğer denominator çok küçükse (yaklaşık sıfır) demektir ki ışın düzleme paraleldir çarpma yok
	if (fabs(denominator) < 1e-6) // * burada 1e-6 küçük bir eşik değeri olarak kullanıldı çünkü floating point hesaplamalarda tam sıfır kontrolü güvenilir olmayabilir fabs fonksiyonu mutlak değer alır ve sonuç 1e-6'dan küçükse paralel kabul edilir
		return (false);
	p0_minus_origin = vec_sub(plane->pos, status->ray->origin); // * (PlanePos - RayOrigin)
	numerator = vec_dot(p0_minus_origin, plane->normal); // * (PlanePos - RayOrigin) ile düzlem normalinin noktasal çarpımı
	t = numerator / denominator; // * çarpma t değeri hesaplandı
	// * t değeri belirlenen aralıkta değilse çarpma yok
	if (t < status->t_min || t > status->t_max)
		return (false);
	status->rec->t = t; // * çarpma noktasının t değeri atandı
	status->rec->p = ray_at(*(status->ray), t); // * çarpma noktası hesaplandı
	set_plane_normal(status->rec, status->ray, plane->normal); // * yüzey normali ayarlandı
	status->rec->color = plane->rgb; // * düzlem rengi ayarlandı
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
	obj->type = PLANE; // BUNU KULLANMAYACAĞIM GALİBA
	obj->data = plane_data;
	obj->hit = &hit_plane;
	return (obj);
}
