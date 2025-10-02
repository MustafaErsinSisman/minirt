/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_obj.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yozlu <yozlu@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/15 17:27:19 by yozlu             #+#    #+#             */
/*   Updated: 2025/09/25 07:48:23 by yozlu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minirt.h"

int ambient_obj(char *value, t_obje_list *obj)
{
	char **temp;
	char **rgb;
	int i;
	
	i = -1;
	temp = ft_split(value, ' ');
	if (!temp)
		return 1;
	obj->type = AMBIANT;
	if (ft_atod(temp[1], 0, 1) < 0.0 || ft_atod(temp[1], 0, 1) > 1.0)
		return 1;
	obj->objects.ambiant.range = ft_atod(temp[1], 0, 1);
	rgb = ft_split(temp[2], ',');
	if (!rgb)
		return 1;
	while (rgb[++i])
		if (ft_atoi(rgb[i]) < 0 || ft_atoi(rgb[i]) > 255)
			return 1;
	obj->objects.ambiant.rgb.x = ft_atoi(rgb[0]);	
	obj->objects.ambiant.rgb.y = ft_atoi(rgb[1]);	
	obj->objects.ambiant.rgb.z = ft_atoi(rgb[2]);
	
	//RGB VE TEMP FRELENECEK
	return 0;
}

int camera_obj(char *value, t_obje_list *obj)
{
	char **temp;
	char **xyz;
	char **normal;
	int i;
	
	i = -1;
	temp = ft_split(value, ' ');
	if (!temp)
		return 1;
	obj->type = CAMERA;
	xyz = ft_split(temp[1], ',');
	obj->objects.camera.pos.x = ft_atod(xyz[0], 0, 1);
	obj->objects.camera.pos.y = ft_atod(xyz[1], 0, 1);
	obj->objects.camera.pos.z = ft_atod(xyz[2], 0, 1);
	normal = ft_split(temp[2], ',');
	while (normal[++i])
		if (ft_atod(normal[i], 0, 1) < -1.0 || ft_atod(normal[i], 0, 1) > 1.0)
			return 1;   // kamera normal vektörü neden normalize olmalı bakılacak
	obj->objects.camera.normal.x = ft_atod(normal[0], 0, 1);
	obj->objects.camera.normal.y = ft_atod(normal[1], 0, 1);
	obj->objects.camera.normal.z = ft_atod(normal[2], 0, 1);
	if (ft_atod(temp[3], 0, 1) < 0 || ft_atod(temp[3], 0, 1) > 180)
		return 1;
	obj->objects.camera.fov = ft_atod(temp[3], 0, 1);
	//RGB VE TEMP FRELENECEK
	return 0;
}

int light_obj(char *value, t_obje_list *obj)
{
	char **temp;
	char **xyz;
	int i;
	
	i = -1;
	temp = ft_split(value, ' ');
	if (!temp)
		return 1;
	obj->type = LIGHT;
	xyz = ft_split(temp[1], ',');
	obj->objects.light.pos.x = ft_atod(xyz[0], 0, 1);
	obj->objects.light.pos.y = ft_atod(xyz[1], 0, 1);
	obj->objects.light.pos.z = ft_atod(xyz[2], 0, 1);
	if (ft_atod(temp[2], 0, 1) < 0.0 || ft_atod(temp[2], 0, 1) > 1.0)
		return 1;
	obj->objects.light.range = ft_atod(temp[2], 0, 1);
	//RGB VE TEMP FRELENECEK
	return 0;
}

int sphere_obj(char *value, t_obje_list *obj)
{
	char **temp;
	char **xyz;
	char **rgb;
	int i;
	
	i = -1;
	temp = ft_split(value, ' ');
	if (!temp)
		return 1;
	obj->type = SPHERE;
	xyz = ft_split(temp[1], ',');
	obj->objects.sphere.pos.x = ft_atod(xyz[0], 0, 1);
	obj->objects.sphere.pos.y = ft_atod(xyz[1], 0, 1);
	obj->objects.sphere.pos.z = ft_atod(xyz[2], 0, 1);
	obj->objects.sphere.diameter = ft_atod(temp[2], 0, 1);
	if(obj->objects.sphere.diameter <= 0)
		return 1;
	rgb = ft_split(temp[3], ',');
	if (!rgb)
		return 1;
	while (rgb[++i])
		if (ft_atoi(rgb[i]) < 0 || ft_atoi(rgb[i]) > 255)
			return 1;
	obj->objects.sphere.rgb.x = ft_atod(rgb[0], 0, 1);
	obj->objects.sphere.rgb.y = ft_atod(rgb[1], 0, 1);
	obj->objects.sphere.rgb.z = ft_atod(rgb[2], 0, 1);
	//RGB VE TEMP FRELENECEK
	return 0;
}

