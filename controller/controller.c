/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   controller.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yozlu <yozlu@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/12 18:02:59 by yozlu             #+#    #+#             */
/*   Updated: 2025/12/09 20:44:35 by yozlu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "controller.h"

static int	parse_object_type(char *value, t_obje_list *obj)
{
	if (ft_strncmp(value, "A ", 2) == 0)
		return (ambient_obj(value, obj));
	else if (ft_strncmp(value, "C ", 2) == 0)
		return (camera_obj(value, obj));
	else if (ft_strncmp(value, "L ", 2) == 0)
		return (light_obj(value, obj));
	else if (ft_strncmp(value, "sp ", 3) == 0)
		return (sphere_obj(value, obj));
	else if (ft_strncmp(value, "pl ", 3) == 0)
		return (plane_obj(value, obj));
	else if (ft_strncmp(value, "cy ", 3) == 0)
		return (cylinder_obj(value, obj));
	else
		return (1);
	return (0);
}

void	controller(char **values, t_obje_list **objects)
{
	t_obje_list	*head;
	t_obje_list	*last;
	t_obje_list	*obj;
	int			error;
	int			i;

	head = NULL;
	last = NULL;
	i = 0;
	while (values[i++])
	{
		if (values[i][0] == '\0' || values[i][0] == '#'
			|| values[i][0] == '\n' || values[i][0] == ' '
			|| values[i][0] == '\t')
			continue ;
		obj = ft_malloc(sizeof(t_obje_list));
		if (!obj)
			error_message("Memory allocation failed\n");
		error = parse_object_type(values[i], obj);
		if (error)
			error_message("Invalid value\n");
		add_obj_to_list(&head, &last, obj);
		i++;
	}
	*objects = head;
}
