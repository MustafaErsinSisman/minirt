/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: musisman <musisman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/07 16:12:18 by musisman          #+#    #+#             */
/*   Updated: 2025/09/07 16:12:18 by musisman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vector.h"

t_vector3	new_vector(double new_x, double new_y, double new_z)
{
	t_vector3	new;

	new.x = new_x;
	new.y = new_y;
	new.z = new_z;
	return (new);
}

t_vector3	vec_sum(t_vector3 v1, t_vector3 v2)
{
	return (new_vector(v1.x + v2.x, v1.y + v2.y, v1.z + v2.z));
}

t_vector3	vec_sub(t_vector3 v1, t_vector3 v2)
{
	return (new_vector(v1.x - v2.x, v1.y - v2.y, v1.z - v2.z));
}

t_vector3 vec_mul(t_vector3 v1, t_vector3 v2)
{
    return (new_vector(v1.x * v2.x, v1.y * v2.y, v1.z * v2.z));
}

t_vector3	vec_scale(t_vector3 v1, double k)
{
	return (new_vector(k * v1.x, k * v1.y, k * v1.z));
}
