/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: musisman <musisman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/29 22:09:30 by musisman          #+#    #+#             */
/*   Updated: 2025/11/29 22:09:30 by musisman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minirt.h"

// TODO LİGHT İŞLERİNE İNCELE DETAYLI

// TODO zorunlu kısım bittikten sonra phong aydınlatma modeli ekle sanırım zorunlu bu da phong modeli şudur: ambient, diffuse, specular ışık bileşenleri ile hesaplama yaparız ve nesnenin parlaklığına göre ışık yansımalarını da hesaba katarız bu da kürede beyazı noktaların daha parlak görünmesini sağlar
// Yardımcı: Sahne ışıklarını (geçici olarak) hazırlar
static void	init_scene_lights(t_lighting_data *data)
{
	//TODO İleride bunlar parser'dan gelecek şu an için sabit değerler kullanalım
	data->light.pos = new_vector(10, 10, 10); // * ışık pozisyonu
	data->light.range = 1.0; // * ışık şiddeti
	data->light.rgb = new_vector(1, 1, 1);	// * beyaz ışık
	data->ambient.range = 0.1; // * ortam ışık şiddeti
	data->ambient.rgb = new_vector(1, 1, 1); // * beyaz ortam ışığı
}

static t_vector3	get_ray_color(t_ray ray, t_list *world)
{
	t_hit_record	rec;
	t_hit_status	status;
	t_lighting_data	l_data;

	status.ray = &ray;
	status.t_min = 0.001;
	status.t_max = INFINITY;
	status.rec = &rec;
	if (hit_world(world, &status))
	{
		init_scene_lights(&l_data);
		l_data.obj_col = rec.color;
		l_data.ambient_col = calculate_ambient(l_data.ambient);
		if (is_in_shadow(world, l_data.light, rec.p))
			l_data.diffuse_col = new_vector(0, 0, 0);
		else
			l_data.diffuse_col = calculate_diffuse(l_data.light, &rec);
		// Sonuç = ObjeRengi * (Ambient + Diffuse)
		return (vec_mul(l_data.obj_col,
				vec_sum(l_data.ambient_col, l_data.diffuse_col)));
	}
	return (new_vector(0, 0, 0)); // * arka plan rengi
}

static void	init_viewport_geometry(t_cam_status *cam, t_viewport *vp)
{
	vp->theta = degrees_to_radians(cam->vfov);
	vp->h = tan(vp->theta / 2.0);
	vp->focal_length = 1.0;
	vp->height = 2.0 * vp->h * vp->focal_length;
	vp->width = vp->height * ((double)cam->image_width / cam->image_height);
	cam->w = vec_normalize(vec_scale(cam->orientation, -1));
	// GIMBAL LOCK KORUMASI:
	// Eğer kamera tam tepeye (0,1,0) veya tam dibe (0,-1,0) bakıyorsa,
	// "Yukarı" vektörümüz ile "Bakış" vektörümüz paralel olur.
	// Bu durumda sağ tarafı (u) hesaplayamayız.
	// Çözüm: Kafamızı hafifçe yana yatırıyormuş gibi "Yukarı"yı değiştiririz.
	if (fabs(cam->orientation.y) > 0.99999)
		cam->vup = new_vector(0, 0, 1); // Z eksenini yukarı kabul et
	cam->u = vec_normalize(vec_cross(cam->vup, cam->w));
	cam->v = vec_cross(cam->w, cam->u); 
	vp->view_u = vec_scale(cam->u, vp->width);
	vp->view_v = vec_scale(cam->v, -vp->height); // DİKKAT: -height değil, vektörün tersi
}

void	camera_init(t_cam_status *cam)
{
	t_viewport	vp;

	cam->aspect_ratio = (double)WIDTH / (double)HEIGHT;
	cam->image_width = WIDTH;
	cam->image_height = (int)(cam->image_width / cam->aspect_ratio);
	if (cam->image_height < 1)
		cam->image_height = 1;
	cam->samples_per_pixel = 2; // * EKLENDİ: Her piksel için örnek sayısı ne kadar yüksek olursa render kalitesi o kadar artar ancak performans düşer 100 yaptım çok yüksek 10 bile yüksek ne bu yaw
	cam->pixel_samples_scale = 1.0 / cam->samples_per_pixel; // * EKLENDİ bu değer renk ortalamasını hesaplarken kullanılacak ne kadar çok örnek alınırsa bu değer o kadar küçük olur
	cam->vfov = 90; // TODO parser fov
	cam->lookfrom = new_vector(0, 0, 0); // TODO parser coordinat xyz
	cam->orientation = new_vector(0, 0, -1);// TODO parser normal vector 
	cam->vup = new_vector(0, 1, 0); // TODO NO parser 
	init_viewport_geometry(cam, &vp);
	cam->cam_center = cam->lookfrom;
	cam->delta_u = vec_scale(vp.view_u, 1.0 / cam->image_width);
	cam->delta_v = vec_scale(vp.view_v, 1.0 / cam->image_height);
	vp.v_center = vec_sub(cam->cam_center, vec_scale(cam->w, vec_len(vec_sub(cam->lookfrom, cam->orientation))));
	vp.upper_left = vec_sub(vp.v_center, vec_scale(vp.view_u, 0.5));
	vp.upper_left = vec_sub(vp.upper_left, vec_scale(vp.view_v, 0.5));
	cam->pixel00_loc = vec_sum(vp.upper_left,
			vec_scale(vec_sum(cam->delta_u, cam->delta_v), 0.5));
}

// GÜNCELLENDİ: Çoklu örnekleme (Multi-sampling) yapan render fonksiyonu
void	camera_render(t_cam_status *cam, t_list *world, t_vars *vars)
{
	t_render		ren;

	camera_init(cam);
	ren.y = -1;
	while (ren.y++ < cam->image_height)
	{
		ren.x = -1;
		while (ren.x++ < cam->image_width)
		{
			ren.pixel_color = new_vector(0, 0, 0);
			ren.sample = 0;
			while (ren.sample < cam->samples_per_pixel)
			{
				ren.r = get_ray(cam, ren.x, ren.y);
				ren.pixel_color = vec_sum(ren.pixel_color, get_ray_color(ren.r, world));
				ren.sample++;
			}
			ren.pixel_color = vec_scale(ren.pixel_color, cam->pixel_samples_scale);
			*(unsigned int *)(vars->addr + (ren.y * vars->size_line + ren.x
						* (vars->bpp / 8))) = color(
					(int)(256 * clamp(ren.pixel_color.x, 0.0, 0.999)),
					(int)(256 * clamp(ren.pixel_color.y, 0.0, 0.999)),
					(int)(256 * clamp(ren.pixel_color.z, 0.0, 0.999)));
		}
	}
}
