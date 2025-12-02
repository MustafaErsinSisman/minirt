/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: musisman <musisman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/19 16:19:23 by musisman          #+#    #+#             */
/*   Updated: 2025/10/19 16:19:23 by musisman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_ray	new_ray(t_vector3 origin, t_vector3 direction) // * yeni ışın oluşturma fonksiyonu
{
	t_ray	r;

	r.origin = origin;
	r.direction = direction;
	return (r);
}

t_vector3	ray_at(t_ray r, double t) // * ışının t parametresine göre nokta hesaplama fonksiyonu
{
	return (vec_sum(r.origin, vec_scale(r.direction, t))); // * ışının origin noktasından direction vektörünün t katı kadar ilerlenmiş nokta döndürüldü P(t) = A + t*B formülü kullanıldı burada A ışının origin noktası B ise ışının yön vektörüdür
}

unsigned int	color(int r, int g, int b) // * renk değeri oluşturma fonksiyonu
{
	return ((r << 16) | (g << 8) | b); // * renk değeri döndürüldü bit kaydırma işlemi ile RGB formatında birleştirildi bunun matematiği şu şekilde gelen int rgb değerleri 0-255 aralığında olmalı sonra bit kaydırma işlemi ile 24 bitlik bir unsigned int değeri oluşturuluyor en son gelen değer örneğin r=255, g=0, b=0 ise bu değer 0xFF0000 yani kırmızı renk olarak temsil ediliyor
}


// * EKLENDİ: Piksel karesi içinde rastgele bir sapma vektörü üretir [-0.5, 0.5]
static t_vector3	sample_square(void)
{
	return (new_vector(random_double() - 0.5, random_double() - 0.5, 0));
}

// * EKLENDİ: Verilen i,j pikseli için rastgele sapmalı bir ışın üretir
t_ray	get_ray(t_cam_status *cam, int i, int j)
{
	t_vector3	offset;
	t_vector3	pixel_sample;
	t_vector3	ray_origin;
	t_vector3	ray_direction;

	offset = sample_square();
	// pixel_sample = pixel00 + ((i + offset.x) * delta_u) + ((j + offset.y) * delta_v)
	pixel_sample = vec_sum(cam->pixel00_loc,
			vec_sum(vec_scale(cam->delta_u, i + offset.x),
				vec_scale(cam->delta_v, j + offset.y)));
	ray_origin = cam->cam_center;
	ray_direction = vec_sub(pixel_sample, ray_origin);
	return (new_ray(ray_origin, ray_direction));
}