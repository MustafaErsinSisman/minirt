/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   objects.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: musisman <musisman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/19 16:07:48 by musisman          #+#    #+#             */
/*   Updated: 2025/10/19 16:07:48 by musisman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef OBJECTS_H
# define OBJECTS_H

# include <stdbool.h>

# include "world.h"
# include "sphere.h"
# include "plane.h"
# include "cylinder.h"

struct	s_object;

typedef struct s_ambient
{
	double		range;
	t_vector3	rgb;
}	t_ambient;

typedef struct s_camera
{
	t_vector3	pos;
	t_vector3	normal;
	double		fov;
}	t_camera;

typedef struct s_light
{
	t_vector3	pos;
	double		range;
	// t_vector3 rgb;
}	t_light;

typedef union u_objects // * tüm nesne türlerini içeren union kullanıldı ki tek bir yapı altında tüm nesne türlerine erişilebilsin ve bellek tasarrufu sağlansın
{
	t_ambient	ambiant;
	t_camera	camera;
	t_light		light;
	t_sphere	sphere;
	t_plane		plane;
	t_cylinder	cylinder;
}	t_objects;

typedef enum e_type // * nesne türü enum kullanıldı ki her bir nesne türü için sabit bir değer atansın ve kodun okunabilirliği artsın bellek tasarrufu da sağlar
{
	AMBIANT,
	CAMERA,
	LIGHT,
	SPHERE,
	PLANE,
	CYLINDER
}	t_type;

typedef struct s_object // * render için objeler sadece obje türü ve verisi
{
	t_type		type; // * nesne türü // BEN BUNU KULLANMAYACAĞIM GALİBA
	void		*data; // * nesne verisi
	t_hit_func	hit; // * çarpma fonksiyonu
}	t_object;

typedef struct s_obje_list // * parser için objeler liste yapısı
{
	t_type				type; // * nesne türü
	t_objects			objects; // * nesne verisi
	struct s_obje_list	*next; // * sonraki nesne
}	t_obje_list;

#endif
