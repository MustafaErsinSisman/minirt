/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder_obj.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yozlu <yozlu@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/09 16:27:50 by yozlu             #+#    #+#             */
/*   Updated: 2025/12/09 16:28:10 by yozlu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "controller.h"

static int	check_cylinder_normal(char **normal, t_obje_list *obj)
{
	int	i;

	i = -1;
	while (normal[++i])
	{
		if (ft_atod(normal[i], 0, 1) < -1.0
			|| ft_atod(normal[i], 0, 1) > 1.0)
			return (1);
	}
	obj->objects.cylinder.normal = new_vector(ft_atod(normal[0], 0, 1),
			ft_atod(normal[1], 0, 1), ft_atod(normal[2], 0, 1));
	if (vec_len(new_vector(obj->objects.cylinder.normal.x,
				obj->objects.cylinder.normal.y,
				obj->objects.cylinder.normal.z)) != 1.0)
		return (1);
	return (0);
}

static int	parse_cylinder_rgb(char **rgb, t_obje_list *obj)
{
	int	i;

	i = -1;
	while (rgb[++i])
	{
		if (ft_atoi(rgb[i]) < 0 || ft_atoi(rgb[i]) > 255)
			return (1);
	}
	obj->objects.cylinder.rgb = new_vector(ft_atoi(rgb[0]) / 255.0,
			ft_atoi(rgb[1]) / 255.0, ft_atoi(rgb[2]) / 255.0);
	return (0);
}

static int	check_cylinder_params(char **temp, t_obje_list *obj)
{
	obj->objects.cylinder.diameter = ft_atod(temp[3], 0, 1);
	if (obj->objects.cylinder.diameter <= 0)
		return (1);
	obj->objects.cylinder.height = ft_atod(temp[4], 0, 1);
	if (obj->objects.cylinder.height <= 0)
		return (1);
	return (0);
}

int	cylinder_obj(char *value, t_obje_list *obj)
{
	char	**temp;
	char	**xyz;
	char	**normal;
	char	**rgb;

	temp = ft_split(value, ' ');
	if (!temp)
		return (1);
	obj->type = CYLINDER;
	xyz = ft_split(temp[1], ',');
	obj->objects.cylinder.pos = new_vector(ft_atod(xyz[0], 0, 1),
			ft_atod(xyz[1], 0, 1), ft_atod(xyz[2], 0, 1));
	normal = ft_split(temp[2], ',');
	if (check_cylinder_normal(normal, obj))
		return (1);
	if (check_cylinder_params(temp, obj))
		return (1);
	rgb = ft_split(temp[5], ',');
	return (parse_cylinder_rgb(rgb, obj));
}
