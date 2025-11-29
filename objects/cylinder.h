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