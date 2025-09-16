/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   controller.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yozlu <yozlu@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/12 18:02:59 by yozlu             #+#    #+#             */
/*   Updated: 2025/09/16 16:39:25 by yozlu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minirt.h"

int controller(char **values)
{
    t_obje_list *head = NULL;
    t_obje_list *last = NULL;
    int i;
    i = 0;
    while (values[i])
    {
        t_obje_list *obj; 
        obj = malloc(sizeof(t_obje_list));
        if (!ft_strcmp(values[i], "A "))
            return ambient_obj(values[i], obj);
        else if (!ft_strcmp(values[i], "C "))
            return camera_obj(values[i], obj);
        else if (!ft_strcmp(values[i], "L "))
        {
            // IŞIK FONKSİYONU
        }
        else if (!ft_strcmp(values[i], "sp "))
        {
            // KARE FONKSİYONU 
        }
        else if (!ft_strcmp(values[i], "pl "))
        {
            // DÜZLEM FONKSİYONU
        }
        else if (!ft_strcmp(values[i], "cy "))
        {
            // SİLİNDİR FONKSİYONU
        }
        else
            return /*free gelcek*/ 1;
        add_obj_to_list(&head, &last, obj);
        i++;
    }
    return 0;
}
