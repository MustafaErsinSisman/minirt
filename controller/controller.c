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

/* minirt/controller/controller.c */

int controller(char **values, t_obje_list **objects)
{
    t_obje_list *head = NULL;
    t_obje_list *last = NULL;
    t_obje_list *obj;
    int i = 0;
    int error = 0; // Hata kontrolü için

    while (values[i])
    {
        obj = ft_malloc(sizeof(t_obje_list));
        if (ft_strncmp(values[i], "A ", 2) == 0) // strncmp daha güvenli
            error = ambient_obj(values[i], obj);
        else if (ft_strncmp(values[i], "C ", 2) == 0)
            error = camera_obj(values[i], obj);
        else if (ft_strncmp(values[i], "L ", 2) == 0)
            error = light_obj(values[i], obj);
        else if (ft_strncmp(values[i], "sp ", 3) == 0)
            error = sphere_obj(values[i], obj);
        else if (ft_strncmp(values[i], "pl ", 3) == 0)
            error = plane_obj(values[i], obj);
        else if (ft_strncmp(values[i], "cy ", 3) == 0)
            error = cylinder_obj(values[i], obj);
        if (error) // Eğer ayrıştırma hatası varsa
            return (1);

        add_obj_to_list(&head, &last, obj); // Listeye ekle
        i++;
    }
    *objects = head; // Listeyi main'e gönder
    return (0);
}
