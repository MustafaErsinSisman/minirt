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

static t_vector3	get_ray_color(t_ray ray, t_list *world)
{
	t_hit_record	rec;
	t_hit_status	status;
	t_vector3		unit_direction;
	double			a;

	status.ray = &ray;
	status.t_min = 0.001;
	status.t_max = INFINITY;
	status.rec = &rec;
	if (hit_world(world, &status))
		return (vec_scale(vec_sum(rec.normal, new_vector(1, 1, 1)), 0.5));
	unit_direction = vec_normalize(ray.direction);
	a = 0.5 * (unit_direction.y + 1.0);
	return (vec_sum(
			vec_scale(new_vector(1.0, 1.0, 1.0), 1.0 - a),
			vec_scale(new_vector(0.5, 0.7, 1.0), a)));
}

void	camera_init(t_cam_status *cam)
{
	double		focal_length;
	double		vp_height;
	double		vp_width;
	t_vector3	vp_u;
	t_vector3	vp_v;
	t_vector3	vp_upper_left;

	cam->image_height = (int)(cam->image_width / cam->aspect_ratio);
	if (cam->image_height < 1)
		cam->image_height = 1;
	cam->center = new_vector(0, 0, 0);
	focal_length = 1.0;
	vp_height = 2.0;
	vp_width = vp_height * ((double)cam->image_width / cam->image_height);
	vp_u = new_vector(vp_width, 0, 0);
	vp_v = new_vector(0, -vp_height, 0);
	cam->pixel_delta_u = vec_scale(vp_u, 1.0 / cam->image_width);
	cam->pixel_delta_v = vec_scale(vp_v, 1.0 / cam->image_height);
	vp_upper_left = vec_sub(cam->center, new_vector(0, 0, focal_length));
	vp_upper_left = vec_sub(vp_upper_left, vec_scale(vp_u, 0.5));
	vp_upper_left = vec_sub(vp_upper_left, vec_scale(vp_v, 0.5));
	cam->pixel00_loc = vec_sum(vp_upper_left,
			vec_scale(vec_sum(cam->pixel_delta_u, cam->pixel_delta_v), 0.5));
}

void	camera_render(t_cam_status *cam, t_list *world, t_vars *vars)
{
	int		i;
	int		j;
	t_vector3	pixel_center;
	t_vector3	ray_direction;
	t_ray		r;
	t_vector3	pixel_color;
	int		color_int;

	camera_init(cam);
	printf("P3\n%d %d\n255\n", cam->image_width, cam->image_height);
	j = 0;
	while (j < cam->image_height)
	{
		printf("\rScanlines remaining: %d ", cam->image_height - j);
		i = 0;
		while (i < cam->image_width)
		{
			pixel_center = vec_sum(cam->pixel00_loc,
						vec_sum(vec_scale(cam->pixel_delta_u, i), 
						vec_scale(cam->pixel_delta_v, j)));
			ray_direction = vec_sub(pixel_center, cam->center);
			r = new_ray(cam->center, ray_direction);
			pixel_color = get_ray_color(r, world);
			color_int = color(
					(int)(255.999 * pixel_color.x),
					(int)(255.999 * pixel_color.y),
					(int)(255.999 * pixel_color.z)
			);
			*(unsigned int *)(vars->addr + (j * vars->size_line + i *
				(vars->bpp / 8))) = color_int;
			i++;
		}
		j++;
	}
}
