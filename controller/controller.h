/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   controller.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yozlu <yozlu@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/24 15:45:03 by yozlu             #+#    #+#             */
/*   Updated: 2025/12/08 19:43:57 by yozlu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CONTROLLER_H
# define CONTROLLER_H

# include <stdio.h>

# include "../gnl/get_next_line.h"
# include "../objects/objects.h"

void	file_extension(char *file_name);
void	add_obj_to_list(t_obje_list **head, t_obje_list **last, t_obje_list *new_obj);
int	controller(char **values, t_obje_list **objects);
int	chr_control(char **values);
int	ambient_obj(char *value, t_obje_list *obj);
int	camera_obj(char *value, t_obje_list *obj);
int	light_obj(char *value, t_obje_list *obj);
int	sphere_obj(char *value, t_obje_list *obj);
int plane_obj(char *value, t_obje_list *obj);
int cylinder_obj(char *value, t_obje_list *obj);

#endif
