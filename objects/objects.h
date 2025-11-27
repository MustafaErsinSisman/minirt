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

# include "../vector/vector.h"
# include <stdbool.h>

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

typedef struct s_sphere
{
	t_vector3	pos;
	double		diameter;
	t_vector3	rgb;
}	t_sphere;

typedef struct s_plane
{
	t_vector3	pos;
	t_vector3	normal;
	t_vector3	rgb;
}	t_plane;

typedef struct s_cylinder
{
	t_vector3	pos;
	t_vector3	normal;
	double		diameter;
	double		height;
	t_vector3	rgb;
}	t_cylinder;

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

typedef struct s_ray
{
	t_vector3	origin; // * ray origin noktası 
	t_vector3	direction; // * ray direction vektörü 
}	t_ray;

typedef struct s_hit_record // * çarpma kaydı
{
	t_vector3	p; // * çarpma noktası
	t_vector3	normal; // * yüzey normali
	double		t; // * t değeri çarpma noktasına olan uzaklık
	bool		front_face; // * yüzeye dışarıdan mı yoksa içeriden mi çarpıldığı bilgisi
	// t_material	*material; // * malzeme bilgisi çarpılan yüzeyin malzemesi olabilir ileride eklenebilir
}	t_hit_record;

typedef struct s_hit_status // * çarpma durumu
{
	const t_ray		*ray; // * çarpan ışın
	double			t_min; // * minimum t değeri bu değerin altındaki çarpmalar dikkate alınmaz
	double			t_max; // * maximum t değeri bu değerin üzerindeki çarpmalar dikkate alınmaz
	t_hit_record	*rec; // * çarpma kaydı bu yapıya çarpma bilgileri yazılır ve bu bilgiler render fonksiyonunda kullanılır
}	t_hit_status;

typedef bool (*t_hit_func)(struct s_object *object,
	t_hit_status *status); // * çarpma fonksiyonu bu fonksiyon her bir nesne türü için farklı olacak çünkü her bir nesnenin çarpma testi farklıdır pointer to function ile tanımlandı ki her bir nesne türü için farklı fonksiyonlar atanabilsin



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

bool		hit_world(t_list *world, t_hit_status *status); // * dünyadaki nesnelere çarpma testi fonksiyonu
t_object	*new_sphere(t_vector3 center, double diameter); // * yeni küre nesnesi oluşturma fonksiyonu
bool		hit_sphere(t_object *object, t_hit_status *status); // * küre çarpma testi fonksiyonu

#endif
