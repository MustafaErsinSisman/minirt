/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   controller.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yozlu <yozlu@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/12 18:02:59 by yozlu             #+#    #+#             */
/*   Updated: 2025/12/10 16:45:17 by yozlu            ###   ########.fr       */
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

void	controller(char **values, t_obje_list **objects, t_obje_list *head,
		t_obje_list *last)
{
	t_obje_list	*obj;
	char		*line;
	int			error;
	int			i;

	i = -1;
	while (values[++i])
	{
		line = values[i];
		while (*line && (*line == ' ' || *line == '\t' || *line == '\v'
				|| *line == '\f' || *line == '\r'))
			line++;
		if (*line == '\0' || *line == '#' || *line == '\n')
			continue ;
		obj = ft_malloc(sizeof(t_obje_list));
		if (!obj)
			error_message("Memory allocation failed\n");
		error = parse_object_type(line, obj);
		if (error)
			error_message("Invalid value\n");
		add_obj_to_list(&head, &last, obj);
	}
	*objects = head;
}
