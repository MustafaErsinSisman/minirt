/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: musisman <musisman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/07 16:06:18 by musisman          #+#    #+#             */
/*   Updated: 2025/09/07 17:34:44 by musisman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_H
# define MINIRT_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>

# include "minilibx-linux/mlx.h"
# include "vector/vector.h"

typedef struct s_ray
{
	t_vector3 origin;
	t_vector3 direction;
}t_ray;

typedef struct s_ambient
{
	double		range;
	t_vector3	rgb;
}t_ambient;

typedef struct s_camera
{
	t_vector3	pos;
	t_vector3	normal;
	double		fov;
}t_camera;

typedef struct s_light
{
	t_vector3	pos;
	double		range;
	// t_vector3 rgb;
}t_light;

typedef struct s_sphere
{
	t_vector3	pos;
	double		diameter;
	t_vector3	rgb;
}t_sphere;

typedef struct s_plane
{
	t_vector3	pos;
	t_vector3	normal;
	t_vector3	rgb;
}t_plane;

typedef struct s_cylinder
{
	t_vector3	pos;
	t_vector3	normal;
	double		diameter;
	double		height;
	t_vector3	rgb;
}t_cylinder;

typedef union u_objects
{
	t_ambient	ambiant;
	t_camera	camera;
	t_light		light;
	t_sphere	sphere;
	t_plane		plane;
	t_cylinder	cylinder;
}t_objects;

typedef enum e_type
{
	AMBIANT,
	CAMERA,
	LIGHT,
	SPHERE,
	PLANE,
	CYLINDER
}t_type;

typedef struct s_obje_list
{
	t_type			type;
	t_objects		objects;
	struct s_obje_list	*next;
}t_obje_list;

#endif
