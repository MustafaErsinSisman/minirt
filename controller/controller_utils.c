/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   controller_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yozlu <yozlu@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/09 18:12:50 by yozlu             #+#    #+#             */
/*   Updated: 2025/09/12 18:57:56 by yozlu            ###   ########.fr       */
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

int	ft_strcmp(const char *str1, const char *str2)
{
	while (*str2 == '0')
		str2++;
	while (*str1 == '0')
		str1++;
	while (*str1 && (*str1 == *str2))
	{
		str1++;
		str2++;
	}
	return (*str1 - *str2);
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

