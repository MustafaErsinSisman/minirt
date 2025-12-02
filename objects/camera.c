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

// TODO zorunlu kısım bittikten sonra phong aydınlatma modeli ekle sanırım zorunlu bu da phong modeli şudur: ambient, diffuse, specular ışık bileşenleri ile hesaplama yaparız ve nesnenin parlaklığına göre ışık yansımalarını da hesaba katarız bu da kürede beyazı noktaların daha parlak görünmesini sağlar
// Yardımcı: Sahne ışıklarını (geçici olarak) hazırlar
static void	init_scene_lights(t_lighting_data *data)
{
	//TODO İleride bunlar parser'dan gelecek
	data->light.pos = new_vector(10, 10, 10); // * ışık pozisyonu
	data->light.range = 1.0; // * ışık şiddeti
	data->light.rgb = new_vector(1, 1, 1);	// * beyaz ışık
	data->ambient.range = 0.1; // * ortam ışık şiddeti
	data->ambient.rgb = new_vector(1, 1, 1); // * beyaz ortam ışığı
	// * Obje rengi şimdilik kırmızı (normalde sphere->rgb olacak)
	data->obj_col = new_vector(1, 1, 1); // hawali renk :D
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
		l_data.ambient_col = calculate_ambient(l_data.ambient);
		l_data.diffuse_col = calculate_diffuse(l_data.light, &rec);
		// Sonuç = ObjeRengi * (Ambient + Diffuse)
		return (vec_mul(l_data.obj_col,
				vec_sum(l_data.ambient_col, l_data.diffuse_col)));
	}
	return (new_vector(0, 0, 0)); // * arka plan rengi
}

void	camera_init(t_cam_status *cam)
{
	t_viewport	vp;

	cam->aspect_ratio = (double)WIDTH / (double)HEIGHT;
	cam->image_width = WIDTH;
	cam->image_height = (int)(cam->image_width / cam->aspect_ratio);
	if (cam->image_height < 1)
		cam->image_height = 1;
	cam->samples_per_pixel = 5; // * EKLENDİ: Her piksel için örnek sayısı ne kadar yüksek olursa render kalitesi o kadar artar ancak performans düşer 100 yaptım çok yüksek 10 bile yüksek ne bu yaw
	cam->pixel_samples_scale = 1.0 / cam->samples_per_pixel; // * EKLENDİ bu değer renk ortalamasını hesaplarken kullanılacak ne kadar çok örnek alınırsa bu değer o kadar küçük olur
	cam->cam_center = new_vector(0, 0, 0);
	vp.focal_length = 1.0;
	vp.height = 2.0;
	vp.width = vp.height * ((double)cam->image_width / cam->image_height);
	vp.view_u = new_vector(vp.width, 0, 0);
	vp.view_v = new_vector(0, -vp.height, 0);
	cam->delta_u = vec_scale(vp.view_u, 1.0 / cam->image_width);
	cam->delta_v = vec_scale(vp.view_v, 1.0 / cam->image_height);
	vp.upper_left = vec_sub(cam->cam_center, new_vector(0, 0, vp.focal_length));
	vp.upper_left = vec_sub(vp.upper_left, vec_scale(vp.view_u, 0.5));
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
