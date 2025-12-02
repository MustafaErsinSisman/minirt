/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   world.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: musisman <musisman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/28 18:19:26 by musisman          #+#    #+#             */
/*   Updated: 2025/11/28 18:19:26 by musisman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef WORLD_H
# define WORLD_H

# include "../vector/vector.h"

typedef struct s_object		t_object;
typedef struct s_hit_status	t_hit_status;

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
	t_vector3	color;
}	t_hit_record;

typedef struct s_hit_status // * çarpma durumu
{
	const t_ray		*ray; // * çarpan ışın
	double			t_min; // * minimum t değeri bu değerin altındaki çarpmalar dikkate alınmaz
	double			t_max; // * maximum t değeri bu değerin üzerindeki çarpmalar dikkate alınmaz
	t_hit_record	*rec; // * çarpma kaydı bu yapıya çarpma bilgileri yazılır ve bu bilgiler render fonksiyonunda kullanılır
}	t_hit_status;

typedef bool	(*t_hit_func)(struct s_object *object,
	t_hit_status *status); // * çarpma fonksiyonu bu fonksiyon her bir nesne türü için farklı olacak çünkü her bir nesnenin çarpma testi farklıdır pointer to function ile tanımlandı ki her bir nesne türü için farklı fonksiyonlar atanabilsin

bool		hit_world(t_list *world, t_hit_status *status); // * dünyadaki nesnelere çarpma testi fonksiyonu

#endif
