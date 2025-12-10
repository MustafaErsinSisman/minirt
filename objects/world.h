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
	t_vector3	origin;
	t_vector3	direction;
}	t_ray;

typedef struct s_hit_record
{
	t_vector3	p;
	t_vector3	normal;
	double		t;
	bool		front_face;
	t_vector3	color;
}	t_hit_record;

typedef struct s_hit_status
{
	const t_ray		*ray;
	double			t_min;
	double			t_max;
	t_hit_record	*rec;
}	t_hit_status;

typedef bool	(*t_hit_func)(struct s_object *object, t_hit_status *status);
bool	hit_world(t_list *world, t_hit_status *status);

#endif
