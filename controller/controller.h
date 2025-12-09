/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   controller.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yozlu <yozlu@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/24 15:45:03 by yozlu             #+#    #+#             */
/*   Updated: 2025/12/09 20:44:35 by yozlu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CONTROLLER_H
# define CONTROLLER_H

# include <stdio.h>

# include "../gnl/get_next_line.h"
# include "../objects/objects.h"

void	file_extension(char *file_name);
void	add_obj_to_list(t_obje_list **head, t_obje_list **last,
			t_obje_list *new_obj);
void	controller(char **values, t_obje_list **objects);
void	error_message(char *message);
void	chr_control(char **values);
char	*check_if_number(char *str);
int		ambient_obj(char *value, t_obje_list *obj);
int		camera_obj(char *value, t_obje_list *obj);
int		light_obj(char *value, t_obje_list *obj);
int		check_cylinder_params(char **temp, t_obje_list *obj);
int		sphere_obj(char *value, t_obje_list *obj);
int		plane_obj(char *value, t_obje_list *obj);
int		cylinder_obj(char *value, t_obje_list *obj);

#endif
