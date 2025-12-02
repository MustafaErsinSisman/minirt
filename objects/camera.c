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

// TODO zorunlu kısım bittikten sonra phong aydınlatma modeli ekle

static t_vector3    get_ray_color(t_ray ray, t_list *world)
{
    t_hit_record    rec;
    t_hit_status    status;
//     t_vector3       final_color;
    t_light     light;
    t_ambient   ambient;

    light.pos = new_vector(10, 10, 10); // Işık konumu (Sağ üst arka)
    light.range = 1.0;                  // Tam parlaklık
	light.rgb = new_vector(1, 1, 1);    // Beyaz ışık daha sonra renk eklenebilir
    ambient.range = 0.1;                // %10 Ortam ışığı (Karanlık yerler simsiyah olmasın)
    ambient.rgb = new_vector(1, 1, 1);  // Beyaz ortam
    status.ray = &ray;
    status.t_min = 0.001;
    status.t_max = INFINITY;
    status.rec = &rec;
    if (hit_world(world, &status))
    {
        t_vector3 ambient_component = vec_scale(ambient.rgb, ambient.range);
        t_vector3 light_dir = vec_sub(light.pos, rec.p);
        light_dir = vec_normalize(light_dir);
        double diff = vec_dot(rec.normal, light_dir);
        if (diff < 0) diff = 0;
        	t_vector3 diffuse_component = vec_scale(light.rgb, diff * light.range);
        t_vector3 object_color = new_vector(1, 0, 0);
        t_vector3 total_light = vec_sum(ambient_component, diffuse_component);
        return (vec_mul(object_color, total_light));
    }
    t_vector3 unit_dir = vec_normalize(ray.direction);
    double a = 0.5 * (unit_dir.y + 1.0);
    return (vec_sum(
            vec_scale(new_vector(1.0, 1.0, 1.0), 1.0 - a),
            vec_scale(new_vector(0.5, 0.7, 1.0), a)));
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

// * EKLENDİ: Piksel karesi içinde rastgele bir sapma vektörü üretir [-0.5, 0.5]
static t_vector3	sample_square(void)
{
	return (new_vector(random_double() - 0.5, random_double() - 0.5, 0));
}

// * EKLENDİ: Verilen i,j pikseli için rastgele sapmalı bir ışın üretir
static t_ray	get_ray(t_cam_status *cam, int i, int j)
{
	t_vector3	offset;
	t_vector3	pixel_sample;
	t_vector3	ray_origin;
	t_vector3	ray_direction;

	offset = sample_square();
	// pixel_sample = pixel00 + ((i + offset.x) * delta_u) + ((j + offset.y) * delta_v)
	pixel_sample = vec_sum(cam->pixel00_loc,
			vec_sum(vec_scale(cam->delta_u, i + offset.x),
				vec_scale(cam->delta_v, j + offset.y)));
	ray_origin = cam->cam_center;
	ray_direction = vec_sub(pixel_sample, ray_origin);
	return (new_ray(ray_origin, ray_direction));
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
