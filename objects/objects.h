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
# include "ambient.h"
# include "light.h"
# include "camera.h"

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

typedef struct s_object
{
	t_type		type;
	void		*data;
	t_hit_func	hit;
}	t_object;

typedef struct s_obje_list
{
	t_type				type;
	t_objects			objects;
	struct s_obje_list	*next;
}	t_obje_list;

#endif
