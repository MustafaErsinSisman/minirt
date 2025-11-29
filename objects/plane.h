/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   plane.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: musisman <musisman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/28 18:12:04 by musisman          #+#    #+#             */
/*   Updated: 2025/11/28 18:12:04 by musisman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PLANE_H
# define PLANE_H

typedef struct s_plane
{
	t_vector3	pos;
	t_vector3	normal;
	t_vector3	rgb;
}	t_plane;

// TODO Aynısını plane için yap

// t_object	*new_sphere(t_vector3 center, double diameter);
// bool		hit_sphere(t_object *object, t_hit_status *status);
#endif
