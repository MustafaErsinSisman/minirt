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

typedef struct s_camera
{
	t_vector3	pos;
	t_vector3	normal;
	double		fov;
}	t_camera; // parser için 

typedef struct s_viewport
{
	double		focal_length;
	double		height;
	double		width;
	t_vector3	view_u;
	t_vector3	view_v;
	t_vector3	upper_left;
	double		theta; // Radyan cinsinden açı
	double		h;     // Viewport yarı yüksekliği oranı
	t_vector3	v_center;
}	t_viewport;

typedef struct s_render
{
	int			sample;
	t_vector3	pixel_color;
	t_ray		r;
	int			x;
	int			y;
}	t_render;

typedef struct s_cam_status
{
	double		aspect_ratio;
	int			image_width;
	int			image_height;
	int			samples_per_pixel; // * EKLENDİ: Örnek sayısı (örn: 100) bu, her piksel için kaç tane rastgele örnek alınacağını belirtir
	double		pixel_samples_scale; // * EKLENDİ: 1.0 / samples_per_pixel bu, renk ortalamasını hesaplarken kullanılır
	double		vfov;
	t_vector3	lookfrom;	// Kameranın durduğu yer (Point3)
	t_vector3	orientation; // YENİ: Yön Vektörü (Örn: 0,0,1) - lookat SİLİNDİ
	t_vector3	vup;		// Kameranın "Yukarı" vektörü (Başın tavanı nereye bakıyor?)
	t_vector3	u;			// Kamera Sağ
	t_vector3	v;			// Kamera Yukarı
	t_vector3	w;			// Kamera Arkası (Bakışın tersi)
	t_vector3	cam_center;
	t_vector3	pixel00_loc;
	t_vector3	delta_u;
	t_vector3	delta_v;
}	t_cam_status;

void	camera_init(t_cam_status *cam);
void	camera_render(t_cam_status *cam, t_list *world, struct s_vars *vars);

#endif