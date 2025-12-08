/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   controller.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yozlu <yozlu@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/12 18:02:59 by yozlu             #+#    #+#             */
/*   Updated: 2025/12/08 19:45:02 by yozlu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "controller.h"

int controller(char **values, t_obje_list *objects)
{
    t_obje_list *head = NULL;
    t_obje_list *last = NULL;
    int i;
    i = 0;
    while (values[i])
    {
        t_obje_list *obj; 
        obj = ft_malloc(sizeof(t_obje_list));
        if (!ft_strcmp(values[i], "A "))
            return ambient_obj(values[i], obj);
        else if (!ft_strcmp(values[i], "C "))
            return camera_obj(values[i], obj);
        else if (!ft_strcmp(values[i], "L "))
            return light_obj(values[i], obj);
        else if (!ft_strcmp(values[i], "sp "))
            return sphere_obj(values[i], obj);
        else if (!ft_strcmp(values[i], "pl "))
            return plane_obj(values[i], obj);
        else if (!ft_strcmp(values[i], "cy "))
            return cylinder_obj(values[i], obj);
        else
            return /*free gelcek*/ 1;
        add_obj_to_list(&head, &last, obj);
        i++;
    }
    objects = head;
    return 0;
}
