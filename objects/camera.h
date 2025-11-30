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

struct	s_vars;

typedef struct s_viewport
{
	double		focal_length;
	double		height;
	double		width;
	t_vector3	view_u;
	t_vector3	view_v;
	t_vector3	upper_left;
}	t_viewport;

typedef struct s_render
{
	t_vector3	pxl_cent; // * her bir pikselin tam ortasının koordinatlarını tutacak
	t_vector3	r_direc; // * her bir piksel için oluşturulacak ışın yön vektörü
	t_ray		r; // * her bir piksel için oluşturulacak ışın
	t_vector3	pxl_clr; // * her bir pikselin rengi
	int		clr; // * her bir pikselin renk değeri
}	t_render;

typedef struct s_cam_status
{
    double      aspect_ratio;
    int         image_width;
    int         image_height;
    t_vector3   cam_center;
    t_vector3   pixel00_loc;
    t_vector3   delta_u;
    t_vector3   delta_v;
    
}   t_cam_status;

void    camera_init(t_cam_status *cam);
void    camera_render(t_cam_status *cam, t_list *world, struct s_vars *vars);

#endif