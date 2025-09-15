/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_obj.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yozlu <yozlu@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/15 17:27:19 by yozlu             #+#    #+#             */
/*   Updated: 2025/09/15 18:02:28 by yozlu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minirt.h"

int ambient_obj(char *value, t_obje_list *obj)
{
	char **temp;
	char **rgb;
	
	temp = ft_split(value, ' ');
	if (!temp)
	{
		// hata durumu
	}
	obj->type = AMBIANT;
	obj->objects.ambiant.range = 
}