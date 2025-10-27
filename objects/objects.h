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

typedef union u_objects
{
	t_ambient	ambiant;
	t_camera	camera;
	t_light		light;
	t_sphere	sphere;
	t_plane		plane;
	t_cylinder	cylinder;
}	t_objects;

typedef enum e_type
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
	t_vector3	origin;
	t_vector3	direction;
}	t_ray;

typedef struct s_hit_record
{
	t_vector3	p;
	t_vector3	normal;
	double		t;
	// t_material	*material;
}	t_hit_record;

typedef struct s_hit_status
{
	const t_ray		*ray;
	double			t_min;
	double			t_max;
	t_hit_record	*rec;
}	t_hit_status;

typedef bool (*t_hit_func)(struct s_object *object,
	t_hit_status *status);

typedef struct s_object // * render için objeler
{
	t_type		type;
	void		*data;
	t_hit_func	hit;
}	t_object;

typedef struct s_obje_list // * parser için objeler
{
	t_type				type;
	t_objects			objects;
	struct s_obje_list	*next;
}	t_obje_list;

bool		hit_world(t_list *world, t_hit_status *status);
t_object	*new_sphere(t_vector3 center, double diameter);
bool		hit_sphere(t_object *object, t_hit_status *status);

#endif
