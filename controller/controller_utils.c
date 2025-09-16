/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   controller_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yozlu <yozlu@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/09 18:12:50 by yozlu             #+#    #+#             */
/*   Updated: 2025/09/16 15:48:19 by yozlu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minirt.h"

void add_obj_to_list(t_obje_list **head, t_obje_list **last, t_obje_list *new_obj)
{
    new_obj->next = NULL;
    if (!*head)
        *head = new_obj;      // liste boşsa başı belirle
    else
        (*last)->next = new_obj; // son elemana bağla

    *last = new_obj;            // son elemanı güncelle
}

int chr_control(char **values)
{
	int i;
	int count;

	i = 0;
	count = 0;
	while (values[i])
	{
		if (ft_strcmp(values[i], "A ") || ft_strcmp(values[i], "C "))
			count++;
		i++;
	}
	if (count >= 3)
		return 1;
	return 0;
}

void	file_extension(char *file_name)
{
	int len; 
    len = ft_strlen(file_name);

	if (len < 4 || ft_strcmp(file_name + len - 3, ".rt") || file_name[len - 4] == '/')
    {
        //hata durumu
    }
}

