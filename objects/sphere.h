/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sphere.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: musisman <musisman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/28 17:49:40 by musisman          #+#    #+#             */
/*   Updated: 2025/11/28 17:49:40 by musisman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SPHERE_H
# define SPHERE_H

# include "../vector/vector.h"

typedef struct s_object		t_object;
typedef struct s_hit_status	t_hit_status;

typedef struct s_sphere
{
	t_vector3	pos;
	double		diameter;
	t_vector3	rgb;
}	t_sphere;

t_object	*new_sphere(t_vector3 center, double diameter); // * yeni küre nesnesi oluşturma fonksiyonu
bool		hit_sphere(t_object *object, t_hit_status *status); // * küre çarpma testi fonksiyonu

#endif
