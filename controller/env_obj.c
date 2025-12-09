/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_obj.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yozlu <yozlu@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/15 17:27:19 by yozlu             #+#    #+#             */
/*   Updated: 2025/12/09 19:33:05 by yozlu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "controller.h"

/*
** Bu fonksiyon string içinde sayısal olmayan bir karakter (harf vb.) var mı diye bakar.
** Eğer geçerli bir sayı formatıysa stringin kendisini döndürür (böylece atoi/atod içine yazılabilir).
** Eğer geçersizse error_message ile programı sonlandırır.
*/
static char	*check_if_number(char *str)
{
	int	i;

	i = 0;
	if (!str || !str[0])
		error_message("Missing value\n");
	if (str[i] == '-' || str[i] == '+')
		i++;
	while (str[i])
	{
		if (!ft_isdigit(str[i]) && str[i] != '.' && str[i] != '\n')
			error_message("Invalid character found in numeric value\n");
		i++;
	}
	return (str);
}

int	ambient_obj(char *value, t_obje_list *obj)
{
	char	**temp;
	char	**rgb;
	int		i;

	i = -1;
	temp = ft_split(value, ' ');
	if (!temp)
		return (1);
	obj->type = AMBIANT;
	if (ft_atod(check_if_number(temp[1]), 0, 1) < 0.0
		|| ft_atod(check_if_number(temp[1]), 0, 1) > 1.0)
		return (1);
	obj->objects.ambiant.range = ft_atod(check_if_number(temp[1]), 0, 1);
	rgb = ft_split(temp[2], ',');
	if (!rgb)
		return (1);
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
	int		i;

	i = -1;
	temp = ft_split(value, ' ');
	if (!temp)
		return (1);
	obj->type = CAMERA;
	xyz = ft_split(temp[1], ',');
	// XYZ değerlerini kontrol ederek al
	obj->objects.camera.pos = new_vector(
			ft_atod(check_if_number(xyz[0]), 0, 1),
			ft_atod(check_if_number(xyz[1]), 0, 1),
			ft_atod(check_if_number(xyz[2]), 0, 1));
	normal = ft_split(temp[2], ',');
	while (normal[++i])
		if (ft_atod(check_if_number(normal[i]), 0, 1) < -1.0
			|| ft_atod(check_if_number(normal[i]), 0, 1) > 1.0)
			return (1);
	obj->objects.camera.normal = new_vector(ft_atod(check_if_number(normal[0]), 0, 1),
			ft_atod(check_if_number(normal[1]), 0, 1),
			ft_atod(check_if_number(normal[2]), 0, 1));
	// Vektör uzunluğu kontrolü (0 olmaması ve normalize edilmesi için)
	if (vec_len(new_vector(obj->objects.camera.normal.x,
				obj->objects.camera.normal.y,
				obj->objects.camera.normal.z)) == 0.0) // 0 vektörü hatası
		return (1);
	if (ft_atod(check_if_number(temp[3]), 0, 1) < 0
		|| ft_atod(check_if_number(temp[3]), 0, 1) > 180)
		return (1);
	return (obj->objects.camera.fov
		= ft_atod(check_if_number(temp[3]), 0, 1), 0);
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
	obj->objects.light.pos = new_vector(ft_atod(check_if_number(xyz[0]), 0, 1),
			ft_atod(check_if_number(xyz[1]), 0, 1),
			ft_atod(check_if_number(xyz[2]), 0, 1));
	if (ft_atod(check_if_number(temp[2]), 0, 1) < 0.0
		|| ft_atod(check_if_number(temp[2]), 0, 1) > 1.0)
		return (1);
	obj->objects.light.range = ft_atod(check_if_number(temp[2]), 0, 1);
	obj->objects.light.rgb = new_vector(1.0, 1.0, 1.0);
	return (0);
}
