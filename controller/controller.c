/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   controller.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yozlu <yozlu@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/12 18:02:59 by yozlu             #+#    #+#             */
/*   Updated: 2025/09/12 19:04:50 by yozlu            ###   ########.fr       */
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
        if (!ft_strncmp(values[i], "A ", 2))
        {
            ambient_obj(values[i], obj);
        }
        else if (!ft_strncmp(values[i], "C ", 2))
        {
            // KAMERA FONKSİYONU
        }
        else if (!ft_strncmp(values[i], "L ", 2))
        {
            // IŞIK FONKSİYONU
        }
        else if (!ft_strncmp(values[i], "sp ", 2))
        {
            // KARE FONKSİYONU 
        }
        else if (!ft_strncmp(values[i], "pl ", 2))
        {
            // DÜZLEM FONKSİYONU
        }
        else if (!ft_strncmp(values[i], "cy ", 2))
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
