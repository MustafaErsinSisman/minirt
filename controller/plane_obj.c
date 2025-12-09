/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   plane_obj.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yozlu <yozlu@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/09 16:26:28 by yozlu             #+#    #+#             */
/*   Updated: 2025/12/09 16:27:14 by yozlu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "controller.h"

static int	check_plane_normal(char **normal, t_obje_list *obj)
{
	int	i;

	i = -1;
	while (normal[++i])
		if (ft_atod(normal[i], 0, 1) < -1.0
			|| ft_atod(normal[i], 0, 1) > 1.0)
			return (1);
	obj->objects.plane.normal = new_vector(ft_atod(normal[0], 0, 1),
			ft_atod(normal[1], 0, 1), ft_atod(normal[2], 0, 1));
	if (vec_len(new_vector(obj->objects.plane.normal.x,
				obj->objects.plane.normal.y,
				obj->objects.plane.normal.z)) != 1.0)
		return (1);
	return (0);
}

static int	parse_plane_rgb(char **rgb, t_obje_list *obj)
{
	int	i;

	i = -1;
	while (rgb[++i])
	{
		if (ft_atoi(rgb[i]) < 0 || ft_atoi(rgb[i]) > 255)
			return (1);
	}
	obj->objects.plane.rgb = new_vector(ft_atoi(rgb[0]) / 255.0,
			ft_atoi(rgb[1]) / 255.0, ft_atoi(rgb[2]) / 255.0);
	return (0);
}

int	plane_obj(char *value, t_obje_list *obj)
{
	char	**temp;
	char	**xyz;
	char	**normal;
	char	**rgb;

	temp = ft_split(value, ' ');
	if (!temp)
		return (1);
	obj->type = PLANE;
	xyz = ft_split(temp[1], ',');
	obj->objects.plane.pos = new_vector(ft_atod(xyz[0], 0, 1),
			ft_atod(xyz[1], 0, 1), ft_atod(xyz[2], 0, 1));
	normal = ft_split(temp[2], ',');
	if (check_plane_normal(normal, obj))
		return (1);
	rgb = ft_split(temp[3], ',');
	return (parse_plane_rgb(rgb, obj));
}
