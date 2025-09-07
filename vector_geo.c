/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector_geo.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: musisman <musisman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/07 17:19:38 by musisman          #+#    #+#             */
/*   Updated: 2025/09/07 17:38:27 by musisman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vector.h"

double	*vec_dot(t_vector3 *v1, t_vector3 *v2)
{
	double	*dot;

	dot = ft_malloc(sizeof(double));
	if (!dot)
		return (NULL);
	*dot = v1->x * v2->x + v1->y * v2->y + v1->z * v2->z;
	return (dot);
}

t_vector3	*vec_cross(t_vector3 *v1, t_vector3 *v2)
{
	t_vector3	*cross;

	cross = ft_malloc(sizeof(t_vector3));
	if (!cross)
		return (NULL);
	cross->x = (v1->x + v1->y + v1->z) * v2->x;
	cross->y = (v1->x + v1->y + v1->z) * v2->y;
	cross->z = (v1->x + v1->y + v1->z) * v2->z;
	return (cross);
}

double	*vec_len(t_vector3 *v1)
{
	double	*len;

	len = ft_malloc(sizeof(double));
	if (!len)
		return (NULL);
	*len = sqrt(v1->x * v1->x + v1->y * v1->y + v1->z * v1->z);
	return (len);
}

t_vector3	*vec_normalize(t_vector3 *v1)
{
	t_vector3	*normal;

	normal = ft_malloc(sizeof(t_vector3));
	if (!normal)
		return (NULL);
	normal->x = v1->x / *vec_len(v1);
	normal->y = v1->y / *vec_len(v1);
	normal->z = v1->z / *vec_len(v1);
	return (normal);
}
