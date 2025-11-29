/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: musisman <musisman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/29 22:04:06 by musisman          #+#    #+#             */
/*   Updated: 2025/11/29 22:04:06 by musisman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CAMERA_H
# define CAMERA_H

# include "../minirt.h"

struct	s_vars;

typedef struct s_cam_status
{
    double      aspect_ratio;
    int         image_width;
    int         image_height;
    t_vector3   center;
    t_vector3   pixel00_loc;
    t_vector3   pixel_delta_u;
    t_vector3   pixel_delta_v;
    
}   t_cam_status;

void    camera_init(t_cam_status *cam);
void    camera_render(t_cam_status *cam, t_list *world, t_vars *vars);

#endif