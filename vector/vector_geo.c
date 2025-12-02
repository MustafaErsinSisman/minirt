/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector_geo.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: musisman <musisman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/07 17:19:38 by musisman          #+#    #+#             */
/*   Updated: 2025/12/02 15:29:22 by musisman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vector.h"

double	vec_dot(t_vector3 v1, t_vector3 v2)
{
	return (v1.x * v2.x + v1.y * v2.y + v1.z * v2.z);
}

t_vector3	vec_cross(t_vector3 v1, t_vector3 v2)
{
	return (new_vector(v1.y * v2.z - v1.z * v2.y,
			v1.z * v2.x - v1.x * v2.z,
			v1.x * v2.y - v1.y * v2.x));
}

double	vec_len(t_vector3 v1)
{
	return (sqrt(v1.x * v1.x + v1.y * v1.y + v1.z * v1.z));
}

t_vector3	vec_normalize(t_vector3 v1)
{
	if (vec_len(v1) > 0)
		return (new_vector(v1.x / vec_len(v1), v1.y / vec_len(v1), v1.z / vec_len(v1)));
	else
		return (new_vector(0, 0, 0));
}
