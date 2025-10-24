/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   controller_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yozlu <yozlu@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/09 18:12:50 by yozlu             #+#    #+#             */
/*   Updated: 2025/10/24 16:34:59 by yozlu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "controller.h"

void add_obj_to_list(t_obje_list **head, t_obje_list **last, t_obje_list *new_obj)
{
    new_obj->next = NULL;
    if (!*head)
        *head = new_obj;      // liste boşsa başı belirle
    else
        (*last)->next = new_obj; // son elemana bağla

    *last = new_obj;            // son elemanı güncelle
}

char 	*ft_strcat(char *restrict dst, const char *restrict src)
{
    ft_strlcpy(dst + ft_strlen(dst), src, ft_strlen(dst) + ft_strlen(src));
    return dst;
}

int chr_control(char **values)
{
	int i;
	int count;
	char *control;

	count = 0;
	i = -1;
	control = ft_strdup("");
	while (values[++i])
	{	
		if (ft_strcmp(values[i], "A ") || ft_strcmp(values[i], "C ") || ft_strcmp(values[i], "L ")) // L de eklenecek
		{
			if (ft_strlen(control) < 3)
				control = ft_strcat(control, ft_substr(values[i], 0, 1));
			count++;	
		}
	}
	if (count >= 4 || !ft_strchr(control, 'A') || !ft_strchr(control, 'C') || !ft_strchr(control, 'L'))
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

