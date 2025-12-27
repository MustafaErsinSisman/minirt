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

static t_vector3	get_ray_color(t_ray ray, t_data *data)
{
	t_hit_record	rec;
	t_hit_status	status;
	t_lighting_data	l_data;

	status.ray = &ray;
	status.t_min = 0.001;
	status.t_max = INFINITY;
	status.rec = &rec;
	if (hit_world(data->world, &status))
	{
		l_data.light = data->light;
		l_data.ambient = data->ambient;
		l_data.obj_col = rec.color;
		l_data.ambient_col = calculate_ambient(l_data.ambient);
		if (is_in_shadow(data->world, l_data.light, rec.p))
			l_data.diffuse_col = new_vector(0, 0, 0);
		else
			l_data.diffuse_col = calculate_diffuse(l_data.light, &rec);
		return (vec_mul(l_data.obj_col,
				vec_sum(l_data.ambient_col, l_data.diffuse_col)));
	}
	return (new_vector(0, 0, 0));
}

static void	init_viewport_geometry(struct s_data *data, t_cam_status *cam,
					t_viewport *vp)
{
	vp->theta = degrees_to_radians(data->camera.fov) / 2.0;
	vp->height = 2.0 * tan(vp->theta);
	vp->width = vp->height * ((double)cam->image_width / cam->image_height);
	cam->w = vec_scale(data->camera.normal, -1);
	if (fabs(data->camera.normal.y) > 0.99999)
		cam->vup = new_vector(0, 0, 1);
	cam->u = vec_normalize(vec_cross(cam->vup, cam->w));
	cam->v = vec_cross(cam->w, cam->u);
	vp->view_u = vec_scale(cam->u, vp->width);
	vp->view_v = vec_scale(cam->v, -vp->height);
}

void	camera_init(t_cam_status *cam, struct s_data *data)
{
	t_viewport	vp;

	cam->aspect_ratio = (double)WIDTH / (double)HEIGHT;
	cam->image_width = WIDTH;
	cam->image_height = (int)(cam->image_width / cam->aspect_ratio);
	if (cam->image_height < 1)
		cam->image_height = 1;
	cam->samples_per_pixel = 2;
	cam->pixel_samples_scale = 1.0 / cam->samples_per_pixel;
	cam->vup = new_vector(0, 1, 0);
	init_viewport_geometry(data, cam, &vp);
	cam->delta_u = vec_scale(vp.view_u, 1.0 / cam->image_width);
	cam->delta_v = vec_scale(vp.view_v, 1.0 / cam->image_height);
	vp.v_center = vec_sub(data->camera.pos, cam->w);
	vp.upper_left = vec_sub(vp.v_center, vec_scale(vp.view_u, 0.5));
	vp.upper_left = vec_sub(vp.upper_left, vec_scale(vp.view_v, 0.5));
	cam->pixel00_loc = vec_sum(vp.upper_left,
			vec_scale(vec_sum(cam->delta_u, cam->delta_v), 0.5));
}

void	camera_render(struct s_data *d, struct s_vars *vars)
{
	t_render		ren;

	camera_init(&(d->c_stat), d);
	ren.y = -1;
	while (++ren.y < d->c_stat.image_height)
	{
		ren.x = -1;
		while (++ren.x < d->c_stat.image_width)
		{
			ren.pxl_clr = new_vector(0, 0, 0);
			ren.sample = -1;
			while (++ren.sample < d->c_stat.samples_per_pixel)
			{
				ren.r = get_ray(d, ren.x, ren.y);
				ren.pxl_clr = vec_sum(ren.pxl_clr,
						get_ray_color(ren.r, d));
			}
			ren.pxl_clr = vec_scale(ren.pxl_clr, d->c_stat.pixel_samples_scale);
			*(unsigned int *)(vars->addr + (ren.y * vars->size_line + ren.x
						* (vars->bpp / 8))) = color(
					(int)(256 * clamp(ren.pxl_clr.x, 0.0, 0.999)),
					(int)(256 * clamp(ren.pxl_clr.y, 0.0, 0.999)),
					(int)(256 * clamp(ren.pxl_clr.z, 0.0, 0.999)));
		}
	}
}
