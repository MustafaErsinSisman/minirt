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