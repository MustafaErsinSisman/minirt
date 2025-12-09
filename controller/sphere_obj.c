/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sphare_obj.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yozlu <yozlu@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/09 16:23:25 by yozlu             #+#    #+#             */
/*   Updated: 2025/12/09 16:26:04 by yozlu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "controller.h"

static int	parse_sphere_rgb(char **rgb, t_obje_list *obj)
{
	int	i;

	i = -1;
	if (!rgb)
		return (1);
	while (rgb[++i])
		if (ft_atoi(rgb[i]) < 0 || ft_atoi(rgb[i]) > 255)
			return (1);
	obj->objects.sphere.rgb = new_vector(ft_atoi(rgb[0]) / 255.0,
			ft_atoi(rgb[1]) / 255.0, ft_atoi(rgb[2]) / 255.0);
	return (0);
}

int	sphere_obj(char *value, t_obje_list *obj)
{
	char	**temp;
	char	**xyz;
	char	**rgb;

	temp = ft_split(value, ' ');
	if (!temp)
		return (1);
	obj->type = SPHERE;
	xyz = ft_split(temp[1], ',');
	obj->objects.sphere.pos = new_vector(ft_atod(xyz[0], 0, 1),
			ft_atod(xyz[1], 0, 1), ft_atod(xyz[2], 0, 1));
	obj->objects.sphere.diameter = ft_atod(temp[2], 0, 1);
	if (obj->objects.sphere.diameter <= 0)
		return (1);
	obj->objects.sphere.radius = obj->objects.sphere.diameter / 2.0;
	rgb = ft_split(temp[3], ',');
	return (parse_sphere_rgb(rgb, obj));
}
