/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sphere_obj.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yozlu <yozlu@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/09 16:23:25 by yozlu             #+#    #+#             */
/*   Updated: 2025/12/09 20:26:33 by yozlu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "controller.h"

static int	parse_sphere_rgb(char **rgb, t_obje_list *obj)
{
	int	i;

	i = -1;
	while (rgb[++i])
		if (ft_atoi(check_if_number(rgb[i])) < 0
			|| ft_atoi(check_if_number(rgb[i])) > 255)
			return (1);
	obj->objects.sphere.rgb = new_vector(
			ft_atoi(check_if_number(rgb[0])) / 255.0,
			ft_atoi(check_if_number(rgb[1])) / 255.0,
			ft_atoi(check_if_number(rgb[2])) / 255.0);
	return (0);
}

int	sphere_obj(char *value, t_obje_list *obj)
{
	char	**temp;
	char	**xyz;
	char	**rgb;

	temp = ft_split(value, ' ');
	if (!temp || !temp[1] || !temp[2] || !temp[3] || temp[4])
		return (1);
	obj->type = SPHERE;
	xyz = ft_split(temp[1], ',');
	if (!xyz || !xyz[0] || !xyz[1] || !xyz[2] || xyz[3])
		return (1);
	obj->objects.sphere.pos = new_vector(
			ft_atod(check_if_number(xyz[0]), 0, 1),
			ft_atod(check_if_number(xyz[1]), 0, 1),
			ft_atod(check_if_number(xyz[2]), 0, 1));
	obj->objects.sphere.diameter = ft_atod(check_if_number(temp[2]), 0, 1);
	if (obj->objects.sphere.diameter <= 0)
		return (1);
	obj->objects.sphere.radius = obj->objects.sphere.diameter / 2.0;
	rgb = ft_split(temp[3], ',');
	if (!rgb || !rgb[0] || !rgb[1] || !rgb[2] || rgb[3])
		return (1);
	return (parse_sphere_rgb(rgb, obj));
}
