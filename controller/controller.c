/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   controller.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yozlu <yozlu@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/09 18:12:50 by yozlu             #+#    #+#             */
/*   Updated: 2025/09/09 18:44:49 by yozlu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minirt.h>

void	file_extension(char *file_name)
{
	int len; 
    len = strlen(file_name);

	if (len < 4 || strcmp(file_name + len - 3, ".rt") || file_name[len - 4] == '/')
    {
        //hata durumu
    }
}

