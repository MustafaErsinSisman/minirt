/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector_geo.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: musisman <musisman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/07 17:19:38 by musisman          #+#    #+#             */
/*   Updated: 2025/09/07 19:21:07 by musisman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vector.h"

double	vec_dot(t_vector3 v1, t_vector3 v2)
{
	double	dot;

	dot = v1.x * v2.x + v1.y * v2.y + v1.z * v2.z;
	return (dot);
}

t_vector3	vec_cross(t_vector3 v1, t_vector3 v2)
{
	t_vector3	cross;

	cross.x = (v1.y * v2.z) - (v1.z * v2.y);
	cross.y = (v1.z * v2.x) - (v1.x * v2.z);
	cross.z = (v1.x * v2.y) - (v1.y * v2.x);
	return (cross);
}

double	vec_len(t_vector3 v1)
{
	double	len;

	len = sqrt(v1.x * v1.x + v1.y * v1.y + v1.z * v1.z);
	return (len);
}

t_vector3	vec_normalize(t_vector3 v1)
{
	t_vector3	normal;
	double	len = vec_len(v1);

	if (len > 0)
	{
		normal.x = v1.x / len;
		normal.y = v1.y / len;
		normal.z = v1.z / len;
	}
	else
	{
		normal.x = 0;
		normal.y = 0;
		normal.z = 0;
	}
	return (normal);
}
