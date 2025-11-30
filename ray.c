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
