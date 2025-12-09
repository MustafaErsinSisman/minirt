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

struct	s_data;
struct	s_vars;

typedef struct s_camera
{
	t_vector3	pos;
	t_vector3	normal;
	double		fov;
}	t_camera;

typedef struct s_viewport
{
	double		focal_length;
	double		height;
	double		width;
	t_vector3	view_u;
	t_vector3	view_v;
	t_vector3	upper_left;
	double		theta;
	double		h;
	t_vector3	v_center;
}	t_viewport;

typedef struct s_render
{
	int			sample;
	t_vector3	pxl_clr;
	t_ray		r;
	int			x;
	int			y;
}	t_render;

typedef struct s_cam_status
{
	double		aspect_ratio;
	int			image_width;
	int			image_height;
	int			samples_per_pixel;
	double		pixel_samples_scale;
	double		vfov;
	t_vector3	lookfrom;
	t_vector3	orientation;
	t_vector3	vup;
	t_vector3	u;
	t_vector3	v;
	t_vector3	w;
	t_vector3	cam_center;
	t_vector3	pixel00_loc;
	t_vector3	delta_u;
	t_vector3	delta_v;
}	t_cam_status;

void	camera_init(t_cam_status *cam, struct s_data *data);
void	camera_render(struct s_data *d, struct s_vars *vars);

#endif