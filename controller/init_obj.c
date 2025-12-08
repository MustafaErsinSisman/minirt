/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_obj.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yozlu <yozlu@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/15 17:27:19 by yozlu             #+#    #+#             */
/*   Updated: 2025/12/08 19:40:53 by yozlu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "controller.h"

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
	obj->objects.ambiant.rgb = new_vector(ft_atoi(rgb[0]), ft_atoi(rgb[1]), ft_atoi(rgb[2]));
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
	obj->objects.camera.pos = new_vector(ft_atod(xyz[0], 0, 1),
		ft_atod(xyz[1], 0, 1), ft_atod(xyz[2], 0, 1));
	normal = ft_split(temp[2], ',');
	while (normal[++i])
		if (ft_atod(normal[i], 0, 1) < -1.0 || ft_atod(normal[i], 0, 1) > 1.0) // vec_len(new_vector(x, y, z) == 1.0)
			return 1;   // kamera normal vektörü neden normalize olmalı bakılacak
	obj->objects.camera.normal = new_vector(ft_atod(normal[0], 0, 1),
		ft_atod(normal[1], 0, 1), ft_atod(normal[2], 0, 1));
	if (vec_len(new_vector(obj->objects.camera.normal.x,
		obj->objects.camera.normal.y, obj->objects.camera.normal.z)) != 1.0)
		return 1;	
	if (ft_atod(temp[3], 0, 1) < 0 || ft_atod(temp[3], 0, 1) > 180)
		return 1;
	return (obj->objects.camera.fov = ft_atod(temp[3], 0, 1), 0);
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
	obj->objects.light.pos = new_vector(ft_atod(xyz[0], 0, 1),
		ft_atod(xyz[1], 0, 1), ft_atod(xyz[2], 0, 1));
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
	obj->objects.sphere.pos = new_vector(ft_atod(xyz[0], 0, 1), ft_atod(xyz[1], 0, 1), ft_atod(xyz[2], 0, 1));
	obj->objects.sphere.diameter = ft_atod(temp[2], 0, 1);
	if(obj->objects.sphere.diameter <= 0)
		return 1;
	rgb = ft_split(temp[3], ',');
	if (!rgb)
		return 1;
	while (rgb[++i])
		if (ft_atoi(rgb[i]) < 0 || ft_atoi(rgb[i]) > 255)
			return 1;
	obj->objects.sphere.rgb = new_vector(ft_atoi(rgb[0]), ft_atoi(rgb[1]), ft_atoi(rgb[2]));
	//RGB VE TEMP FRELENECEK
	return 0;
}

int plane_obj(char *value, t_obje_list *obj)
{
    char **temp;
    char **xyz;
    char **normal;
    char **rgb;
    int i;

    i = -1;
    temp = ft_split(value, ' ');
    if (!temp)
        return 1;
    obj->type = PLANE;
    xyz = ft_split(temp[1], ',');
    obj->objects.plane.pos = new_vector(ft_atod(xyz[0], 0, 1), ft_atod(xyz[1], 0, 1), ft_atod(xyz[2], 0, 1));
    normal = ft_split(temp[2], ',');
    while (normal[++i])
        if (ft_atod(normal[i], 0, 1) < -1.0 || ft_atod(normal[i], 0, 1) > 1.0)
            return 1;
    obj->objects.plane.normal = new_vector(ft_atod(normal[0], 0, 1), ft_atod(normal[1], 0, 1), ft_atod(normal[2], 0, 1));
	if (vec_len(new_vector(obj->objects.plane.normal.x,
		obj->objects.plane.normal.y, obj->objects.plane.normal.z)) != 1.0)
		return 1;
    i = -1;
    rgb = ft_split(temp[3], ',');
    while (rgb[++i])
	{
		if (ft_atoi(rgb[i]) < 0 || ft_atoi(rgb[i]) > 255)
			return 1;
	}
	obj->objects.plane.rgb = new_vector(ft_atoi(rgb[0]), ft_atoi(rgb[1]), ft_atoi(rgb[2]));
    return 0;
}

int cylinder_obj(char *value, t_obje_list *obj)
{
    char **temp;
    char **xyz;
    char **normal;
    char **rgb;
    int i;

    i = -1;
    temp = ft_split(value, ' ');
    if (!temp)
        return 1;
    obj->type = CYLINDER;

    xyz = ft_split(temp[1], ',');
	obj->objects.cylinder.pos = new_vector(ft_atod(xyz[0], 0, 1),
		ft_atod(xyz[1], 0, 1), ft_atod(xyz[2], 0, 1));
    normal = ft_split(temp[2], ',');
    while (normal[++i])
	{
		if (ft_atod(normal[i], 0, 1) < -1.0 || ft_atod(normal[i], 0, 1) > 1.0)
			return 1;
	}
	obj->objects.cylinder.normal = new_vector(ft_atod(normal[0], 0, 1),
		ft_atod(normal[1], 0, 1), ft_atod(normal[2], 0, 1));
	if (vec_len(new_vector(obj->objects.cylinder.normal.x,
		obj->objects.cylinder.normal.y, obj->objects.cylinder.normal.z)) != 1.0)
		return 1;
    obj->objects.cylinder.diameter = ft_atod(temp[3], 0, 1);
    if (obj->objects.cylinder.diameter <= 0)
        return 1;
    obj->objects.cylinder.height = ft_atod(temp[4], 0, 1);
    if (obj->objects.cylinder.height <= 0)
        return 1;
    i = -1;
    rgb = ft_split(temp[5], ',');
    while (rgb[++i])
	{
		if (ft_atoi(rgb[i]) < 0 || ft_atoi(rgb[i]) > 255)
			return 1;
	}
	obj->objects.cylinder.rgb = new_vector(ft_atoi(rgb[0]), ft_atoi(rgb[1]), ft_atoi(rgb[2]));
    return 0;
}
