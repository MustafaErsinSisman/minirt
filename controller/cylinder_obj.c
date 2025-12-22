/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder_obj.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yozlu <yozlu@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/09 16:27:50 by yozlu             #+#    #+#             */
/*   Updated: 2025/12/22 16:00:17 by yozlu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "controller.h"

static int	check_cylinder_params(char **temp, t_obje_list *obj)
{
	obj->objects.cylinder.diameter = ft_atod(check_if_number(temp[3]), 0, 1);
	if (obj->objects.cylinder.diameter <= 0)
		return (1);
	obj->objects.cylinder.height = ft_atod(check_if_number(temp[4]), 0, 1);
	if (obj->objects.cylinder.height <= 0)
		return (1);
	return (0);
}

static int	check_cylinder_normal(char **normal, t_obje_list *obj)
{
	int	i;

	i = -1;
	while (normal[++i])
	{
		if (ft_atod(check_if_number(normal[i]), 0, 1) < -1.0
			|| ft_atod(check_if_number(normal[i]), 0, 1) > 1.0)
			return (1);
	}
	obj->objects.cylinder.normal = new_vector(
			ft_atod(check_if_number(normal[0]), 0, 1),
			ft_atod(check_if_number(normal[1]), 0, 1),
			ft_atod(check_if_number(normal[2]), 0, 1));
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
		if (ft_atoi(check_if_number(rgb[i])) < 0
			|| ft_atoi(check_if_number(rgb[i])) > 255)
			return (1);
	}
	obj->objects.cylinder.rgb = new_vector(
			ft_atoi(check_if_number(rgb[0])) / 255.0,
			ft_atoi(check_if_number(rgb[1])) / 255.0,
			ft_atoi(check_if_number(rgb[2])) / 255.0);
	return (0);
}

static int	parse_cylinder_position(char **temp, t_obje_list *obj)
{
	char	**xyz;

	obj->type = CYLINDER;
	xyz = ft_split(temp[1], ',');
	if (!xyz || !xyz[0] || !xyz[1] || !xyz[2] || xyz[3])
		return (1);
	obj->objects.cylinder.pos = new_vector(
			ft_atod(check_if_number(xyz[0]), 0, 1),
			ft_atod(check_if_number(xyz[1]), 0, 1),
			ft_atod(check_if_number(xyz[2]), 0, 1));
	return (0);
}

int	cylinder_obj(char *value, t_obje_list *obj)
{
	char	**temp;
	char	**normal;
	char	**rgb;

	temp = ft_split(value, ' ');
	if (!temp)
		return (1);
	if (!temp || !temp[1] || !temp[2] || !temp[3]
		|| !temp[4] || !temp[5] || temp[6])
		return (1);
	if (parse_cylinder_position(temp, obj))
		return (1);
	normal = ft_split(temp[2], ',');
	if (!normal || !normal[0] || !normal[1] || !normal[2] || normal[3])
		return (1);
	if (check_cylinder_normal(normal, obj))
		return (1);
	if (check_cylinder_params(temp, obj))
		return (1);
	rgb = ft_split(temp[5], ',');
	if (!rgb || !rgb[0] || !rgb[1] || !rgb[2] || rgb[3])
		return (1);
	return (parse_cylinder_rgb(rgb, obj));
}
