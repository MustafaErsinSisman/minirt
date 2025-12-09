/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_obj.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yozlu <yozlu@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/15 17:27:19 by yozlu             #+#    #+#             */
/*   Updated: 2025/12/09 20:46:11 by yozlu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "controller.h"

static int	check_camera_normal(char **normal, t_obje_list *obj)
{
	int	i;

	i = -1;
	while (normal[++i])
		if (ft_atod(check_if_number(normal[i]), 0, 1) < -1.0
			|| ft_atod(check_if_number(normal[i]), 0, 1) > 1.0)
			return (1);
	obj->objects.camera.normal = new_vector(
			ft_atod(check_if_number(normal[0]), 0, 1),
			ft_atod(check_if_number(normal[1]), 0, 1),
			ft_atod(check_if_number(normal[2]), 0, 1));
	if (vec_len(new_vector(obj->objects.camera.normal.x,
				obj->objects.camera.normal.y,
				obj->objects.camera.normal.z)) == 0.0)
		return (1);
	return (0);
}

int	ambient_obj(char *value, t_obje_list *obj)
{
	char	**temp;
	char	**rgb;
	int		i;

	i = -1;
	temp = ft_split(value, ' ');
	if (!temp || !temp[1] || !temp[2] || temp[3])
		return (1);
	rgb = ft_split(temp[2], ',');
	if (!rgb || !rgb[0] || !rgb[1] || !rgb[2] || rgb[3])
		return (1);
	obj->type = AMBIANT;
	if (ft_atod(check_if_number(temp[1]), 0, 1) < 0.0
		|| ft_atod(check_if_number(temp[1]), 0, 1) > 1.0)
		return (1);
	obj->objects.ambiant.range = ft_atod(check_if_number(temp[1]), 0, 1);
	while (rgb[++i])
		if (ft_atoi(check_if_number(rgb[i])) < 0
			|| ft_atoi(check_if_number(rgb[i])) > 255)
			return (1);
	obj->objects.ambiant.rgb = new_vector(
			ft_atoi(check_if_number(rgb[0])) / 255.0,
			ft_atoi(check_if_number(rgb[1])) / 255.0,
			ft_atoi(check_if_number(rgb[2])) / 255.0);
	return (0);
}

int	camera_obj(char *value, t_obje_list *obj)
{
	char	**temp;
	char	**xyz;
	char	**normal;

	temp = ft_split(value, ' ');
	if (!temp)
		return (1);
	obj->type = CAMERA;
	xyz = ft_split(temp[1], ',');
	obj->objects.camera.pos = new_vector(
			ft_atod(check_if_number(xyz[0]), 0, 1),
			ft_atod(check_if_number(xyz[1]), 0, 1),
			ft_atod(check_if_number(xyz[2]), 0, 1));
	normal = ft_split(temp[2], ',');
	if (check_camera_normal(normal, obj))
		return (1);
	if (ft_atod(check_if_number(temp[3]), 0, 1) < 0
		|| ft_atod(check_if_number(temp[3]), 0, 1) > 180)
		return (1);
	obj->objects.camera.fov = ft_atod(check_if_number(temp[3]), 0, 1);
	return (0);
}

int	light_obj(char *value, t_obje_list *obj)
{
	char	**temp;
	char	**xyz;

	temp = ft_split(value, ' ');
	if (!temp)
		return (1);
	obj->type = LIGHT;
	xyz = ft_split(temp[1], ',');
	obj->objects.light.pos = new_vector(
			ft_atod(check_if_number(xyz[0]), 0, 1),
			ft_atod(check_if_number(xyz[1]), 0, 1),
			ft_atod(check_if_number(xyz[2]), 0, 1));
	if (ft_atod(check_if_number(temp[2]), 0, 1) < 0.0
		|| ft_atod(check_if_number(temp[2]), 0, 1) > 1.0)
		return (1);
	obj->objects.light.range = ft_atod(check_if_number(temp[2]), 0, 1);
	obj->objects.light.rgb = new_vector(1.0, 1.0, 1.0);
	return (0);
}
