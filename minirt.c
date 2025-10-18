/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: musisman <musisman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/07 16:01:24 by musisman          #+#    #+#             */
/*   Updated: 2025/10/18 12:17:50 by musisman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

#define WIDTH 1920.0
// #define ASPECT_RATIO 1.777777778 (16.0 / 9.0)
// #define HEIGHT (WIDTH / ASPECT_RATIO)
#define HEIGHT 1080.0

typedef struct s_vars
{
	void *mlx;
	void *win;
	void *img;
	char *addr;
} t_vars;

int exit_func(t_vars *vars)
{
	mlx_destroy_image(vars->mlx, vars->img);
	mlx_destroy_window(vars->mlx, vars->win);
	mlx_destroy_display(vars->mlx);
	free(vars->mlx);
	ft_free();
	exit(0);
}

int key_hook(int keycode, t_vars *vars)
{
	if (keycode == 65307)  // ESC
		exit_func(vars);
	return (0);
}

unsigned int color(int r, int g, int b)
{
	unsigned int	hex_color;

	hex_color = (r << 16) | (g << 8) | b;
	return hex_color;
}

t_ray new_ray(t_vector3 origin, t_vector3 direction)
{
	t_ray r;
	r.origin = origin;
	r.direction = direction;
	return (r);
}

t_vector3 ray_at(t_ray r, double t)
{
	return (vec_sum(r.origin, vec_scale(r.direction, t)));
}

bool	hit_sphere(t_object *object, const t_ray *r, double t_min,
	double t_max, t_hit_record *rec)
{
	t_sphere	*sphere;
	t_vector3	oc;
	double		a;
	double		half_b;
	double		c;
	double		discriminant;
	double		sqrtd;
	double		root;
	double		radius;

	sphere = (t_sphere *)object->data;
	radius = sphere->diameter / 2.0;
	oc = vec_sub(r->origin, sphere->pos);
	a = vec_dot(r->direction, r->direction);
	half_b = vec_dot(oc, r->direction);
	c = vec_dot(oc, oc) - radius * radius;
	discriminant = half_b * half_b - a * c;
	if (discriminant < 0)
		return (false);
	sqrtd = sqrt(discriminant);
	root = (-half_b - sqrtd) / a;
	if (root < t_min || t_max < root)
	{
		root = (-half_b + sqrtd) / a;
		if (root < t_min || t_max < root)
			return (false);
	}
	rec->t = root;
	rec->p = ray_at(*r, rec->t);
	rec->normal = vec_scale(vec_sub(rec->p, sphere->pos), 1.0 / radius);
	return (true);
}

bool	hit_world(t_list *world, const t_ray *r, double t_min,
	double t_max, t_hit_record *rec)
{
	t_hit_record	temp_rec;
	bool			hit_anything;
	double			closest_so_far;
	t_list			*current_object_node;
	t_object		*current_object;

	hit_anything = false;
	closest_so_far = t_max;
	current_object_node = world;
	while (current_object_node)
	{
		current_object = (t_object *)current_object_node->content;
		if (current_object->hit(current_object, r, t_min,
			closest_so_far, &temp_rec))
		{
			hit_anything = true;
			closest_so_far = temp_rec.t;
			*rec = temp_rec;
		}
		current_object_node = current_object_node->next;
	}
	return (hit_anything);
}

t_object	*new_sphere(t_vector3 center, double diameter)
{
	t_object	*obj;
	t_sphere	*sphere_data;

	obj = ft_malloc(sizeof(t_object));
	sphere_data = ft_malloc(sizeof(t_sphere));
	sphere_data->pos = center;
	sphere_data->diameter = diameter;
	obj->type = SPHERE;
	obj->data = sphere_data;
	obj->hit = &hit_sphere;
	return (obj);
}

unsigned int ray_color(t_ray ray, t_list *world)
{
	t_hit_record	rec;

	if (hit_world(world, &ray, 0.001, INFINITY, &rec))
	{
		t_vector3 n = rec.normal;
		double r1 = 0.5 * (n.x + 1.0);
		double g1 = 0.5 * (n.y + 1.0);
		double b1 = 0.5 * (n.z + 1.0);
		return (color((int)(255.999 * r1), \
			(int)(255.999 * g1), (int)(255.999 * b1)));
	}
	t_vector3 unit_direction = vec_normalize(ray.direction);
	double a = 0.5 * (unit_direction.y + 1.0);
	double r = (1.0 - a) * 1.0 + a * 0.5;
	double g = (1.0 - a) * 1.0 + a * 0.7;
	double b = (1.0 - a) * 1.0 + a * 1.0;
	return color((int)(255.999 * r), (int)(255.999 * g), (int)(255.999 * b));
}

int main(void)
{
	t_vars		vars;
	int			bpp;
	int			line_len;
	int			endian;
	t_list		*world;

	world = NULL;
	ft_lstadd_back(&world, ft_lstnew(new_sphere(new_vector(0, 0, -1), 1.0)));
	ft_lstadd_back(&world, ft_lstnew(new_sphere(new_vector(0, -100.5, -1), 200.0)));

	vars.mlx = mlx_init();
	vars.win = mlx_new_window(vars.mlx, WIDTH, HEIGHT, "miniRT");
	vars.img = mlx_new_image(vars.mlx, WIDTH, HEIGHT);
	vars.addr = mlx_get_data_addr(vars.img, &bpp, &line_len, &endian);

	float		focal_length = 1.0;
	float		view_height = 2.0;
	float		view_width = view_height * (WIDTH / HEIGHT);
	t_vector3	camera_center = new_vector(0, 0, 0);
	t_vector3	view_u = new_vector(view_width, 0, 0);
	t_vector3	view_v = new_vector(0, -view_height, 0);
	t_vector3	delta_view_u = vec_scale(view_u, 1.0 / WIDTH);
	t_vector3	delta_view_v = vec_scale(view_v, 1.0 / HEIGHT);
	t_vector3	view_upper_left = vec_sub(vec_sub(vec_sub(camera_center, \
		new_vector(0, 0, focal_length)), vec_scale(view_u, 0.5)), \
		vec_scale(view_v, 0.5));
	t_vector3	pixel00_loc = vec_sum(view_upper_left, \
		vec_scale(vec_sum(delta_view_u, delta_view_v), 0.5));

	int x;
	int y;
	y = 0;
	while (y < HEIGHT)
	{
		x = 0;
		while (x < WIDTH)
		{
			t_vector3 pixel_center = vec_sum(vec_sum(pixel00_loc, \
				vec_scale(delta_view_u, x)), vec_scale(delta_view_v, y));
			t_vector3 ray_direction = vec_sub(pixel_center, camera_center);
			t_ray r = new_ray(camera_center, ray_direction);
			*(unsigned int *)(vars.addr + y * line_len + x * (bpp / 8)) \
				= ray_color(r, world);
			x++;
		}
		y++;
	}

	mlx_put_image_to_window(vars.mlx, vars.win, vars.img, 0, 0);
	mlx_key_hook(vars.win, key_hook, &vars);
	mlx_hook(vars.win, 17, 0, exit_func, &vars);
	mlx_loop(vars.mlx);
	exit_func(&vars);
	return (0);
}
