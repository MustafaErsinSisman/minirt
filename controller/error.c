/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yozlu <yozlu@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/09 15:34:29 by yozlu             #+#    #+#             */
/*   Updated: 2025/12/09 20:44:35 by yozlu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "controller.h"

void	error_message(char *message)
{
	printf("Error: %s", message);
	ft_free();
	exit(1);
}

char	*check_if_number(char *str)
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

int	check_cylinder_params(char **temp, t_obje_list *obj)
{
	obj->objects.cylinder.diameter = ft_atod(check_if_number(temp[3]), 0, 1);
	if (obj->objects.cylinder.diameter <= 0)
		return (1);
	obj->objects.cylinder.height = ft_atod(check_if_number(temp[4]), 0, 1);
	if (obj->objects.cylinder.height <= 0)
		return (1);
	return (0);
}
