/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: musisman <musisman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/28 18:15:40 by musisman          #+#    #+#             */
/*   Updated: 2025/11/28 18:15:40 by musisman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CYLINDER_H
# define CYLINDER_H

# include "../vector/vector.h"

typedef struct s_object		t_object;
typedef struct s_hit_status	t_hit_status;

typedef struct s_cylinder
{
	t_vector3	pos;
	t_vector3	normal;
	double		diameter;
	double		height;
	t_vector3	rgb;
}	t_cylinder;

// TODO Aynısını cylinder için yap

// t_object	*new_sphere(t_vector3 center, double diameter);
// bool		hit_sphere(t_object *object, t_hit_status *status);
#endif