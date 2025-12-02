/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   light.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: musisman <musisman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/02 15:06:29 by musisman          #+#    #+#             */
/*   Updated: 2025/12/02 15:06:29 by musisman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minirt.h"

t_vector3	calculate_diffuse(t_light light, t_hit_record *rec)
{
	t_vector3	light_dir;
	t_vector3	diffuse_color;
	double		diff;

	// Işık vektörü: Işık Konumu - Çarpma Noktası
	light_dir = vec_sub(light.pos, rec->p);
	light_dir = vec_normalize(light_dir);
	
	// Lambert Cosine Law: Normal ile Işık Vektörü arasındaki açı
	diff = vec_dot(rec->normal, light_dir);
	if (diff < 0)
		diff = 0;
	
	// Diffuse Renk = Işık Rengi * (Açı * Işık Şiddeti)
	diffuse_color = vec_scale(light.rgb, diff * light.range);
	return (diffuse_color);
}

bool	is_in_shadow(t_list *world, t_light light, t_vector3 point) // * noktanın gölgede olup olmadığını kontrol eder
{
	t_vector3		light_dir;
	double			light_dist;
	t_ray			shadow_ray;
	t_hit_record	rec;
	t_hit_status	status;

	// 1. Noktadan Işığa giden vektörü bul
	light_dir = vec_sub(light.pos, point);
	// 2. Işığa olan mesafeyi ölç (Çarpışma bu mesafeden kısaysa gölgedir)
	light_dist = vec_len(light_dir);
	// 3. Gölge ışınını oluştur (Yönü normalize et)
	shadow_ray = new_ray(point, vec_normalize(light_dir));
	status.ray = &shadow_ray;
	// t_min: "Shadow Acne" denilen kendi kendine gölgeleme hatasını önlemek için
	// 0.0 yerine çok küçük bir sayı (epsilon) veriyoruz.
	status.t_min = 0.001; 
	status.t_max = light_dist; // Işıktan daha uzaktaki cisimler gölge yapmaz
	status.rec = &rec;
	if (hit_world(world, &status))
		return (true);
	return (false);
}
