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

t_vector3	*new_vector(double new_x, double new_y, double new_z)
{
	t_vector3	*new;

	new = ft_malloc(sizeof(t_vector3));
	if (!new)
		ft_exit();
	new->x = new_x;
	new->y = new_y;
	new->z = new_z;
	return (new);
}

t_vector3	vec_sum(t_vector3 v1, t_vector3 v2)
{
	t_vector3	sum;

	sum.x = v1.x + v2.x;
	sum.y = v1.y + v2.y;
	sum.z = v1.z + v2.z;
	return (sum);
}

t_vector3	vec_sub(t_vector3 v1, t_vector3 v2)
{
	t_vector3	sub;

	sub.x = v1.x - v2.x;
	sub.y = v1.y - v2.y;
	sub.z = v1.z - v2.z;
	return (sub);
}

t_vector3	vec_scale(t_vector3 v1, double k)
{
	t_vector3	scale;

	scale.x = k * v1.x;
	scale.y = k * v1.y;
	scale.z = k * v1.z;
	return (scale);
}
