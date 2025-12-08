/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   light.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: musisman <musisman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/02 15:06:32 by musisman          #+#    #+#             */
/*   Updated: 2025/12/02 15:06:32 by musisman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIGHT_H
# define LIGHT_H

typedef struct s_light
{
	t_vector3	pos;
	double		range;
	t_vector3 rgb;
}	t_light;

/* minirt.h içine ekle/güncelle */

// Işıklandırma hesabı için yardımcı struct (Norm için)
typedef struct s_lighting_data
{
	t_light		light;
	t_ambient	ambient;
	t_vector3	light_dir;
	t_vector3	ambient_col;
	t_vector3	diffuse_col;
	t_vector3	obj_col;
	double		diff;
}	t_lighting_data;

// Fonksiyonlar
t_vector3	calculate_diffuse(t_light light, t_hit_record *rec);
bool		is_in_shadow(t_list *world, t_light light, t_vector3 point);
// color fonksiyonunun prototipi zaten vardı
#endif