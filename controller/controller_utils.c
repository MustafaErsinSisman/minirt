/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   controller_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yozlu <yozlu@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/09 18:12:50 by yozlu             #+#    #+#             */
/*   Updated: 2025/12/22 16:28:35 by yozlu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "controller.h"

void	add_obj_to_list(t_obje_list **head, t_obje_list **last,
		t_obje_list *new_obj)
{
	new_obj->next = NULL;
	if (!*head)
		*head = new_obj;
	else
		(*last)->next = new_obj;
	*last = new_obj;
}

char	*ft_strcat(char *restrict dst, const char *restrict src)
{
	ft_strlcpy(dst + ft_strlen(dst), src, ft_strlen(dst) + ft_strlen(src));
	return (dst);
}

void	chr_control(char **values)
{
	int		i;
	char	*control;
	char	*line;

	i = -1;
	control = ft_strdup("");
	while (values[++i])
	{
		line = values[i];
		while (*line && (*line == ' ' || *line == '\t'))
			line++;
		if (*line == '\0' || *line == '\n' || *line == '#')
			continue ;
		if (!ft_strncmp(line, "A ", 2) || !ft_strncmp(line, "C ", 2)
			|| !ft_strncmp(line, "L ", 2))
		{
			if (ft_strchr(control, *line))
				error_message("Duplicate object found (A, C or L)\n");
			control = ft_strjoin(control, ft_substr(line, 0, 1));
		}
	}
	if (!ft_strchr(control, 'A') || !ft_strchr(control, 'C'))
		error_message("Invalid number of ambient, camera or light sources\n");
}

void	file_extension(char *file_name)
{
	int	len;

	len = ft_strlen(file_name);
	if (len < 4 || ft_strcmp(file_name + len - 3, ".rt")
		|| file_name[len - 4] == '/')
		error_message("Invalid file extension. Expected a .rt file.\n");
}

char	*check_if_number(char *str)
{
	int	i;
	int	dot;

	i = 0;
	dot = 0;
	while (str && str[i] && (str[i] == ' ' || str[i] == '\t'))
		i++;
	if (!str || !str[i])
		error_message("Missing value\n");
	if (str[i] == '-' || str[i] == '+')
		i++;
	while (str[i])
	{
		if (str[i] == '.')
		{
			if (++dot > 1)
				error_message("Invalid format: Multiple dots\n");
		}
		else if (!ft_isdigit(str[i]) && str[i] != '\n' && str[i] != '\r'
			&& str[i] != ' ' && str[i] != '\t')
			error_message("Invalid character found in numeric value\n");
		i++;
	}
	return (str);
}
