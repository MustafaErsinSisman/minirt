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

typedef struct s_sphere
{
	t_vector3	pos;
	double		diameter;
	double		radius;
	t_vector3	rgb;
}	t_sphere;

t_object	*new_sphere(t_vector3 center, double radius, t_vector3 rgb);
bool		hit_sphere(t_object *object, t_hit_status *status);

#endif
