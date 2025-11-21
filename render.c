/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: musisman <musisman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/19 16:48:50 by musisman          #+#    #+#             */
/*   Updated: 2025/10/19 16:48:50 by musisman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static t_viewport	setup_viewport(void) // TODO world structını al, t_objects_list structı olacak yani
{
	t_viewport	vp;

	vp.focal_length = 1.0; // * focal length yani kamera ile viewport arasındaki mesafe ne kadar büyükse görüntü o kadar yakın olur, ne kadar küçükse görüntü o kadar uzak olur 
	vp.camera_center = new_vector(0, 0, 0); // TODO parserdan gelecek
	vp.view_u = new_vector(2.0 * (WIDTH / HEIGHT), 0, 0); // * aspect ratio yu korumak için width / height ile çarpıldı 2.0 çünkü viewport genişliği 2 birim olarak alındı  bunun sebebi ise x ekseninde -1 den 1 e kadar olan alanı kaplaması yani toplamda 2 birimlik bir genişlik olması gerekiyor 
	vp.view_v = new_vector(0, -2.0, 0); // * -2 olmasının sebebi y ekseninin yukarıdan aşağıya doğru artması sebebi sol üste köşe (0,0) koordinatını vermesi ama matematikte tam tersi y koordinatı aşağıdan yukarıya doğru artar bu yüzden -2 yapıldı sanki y eksenini tersine çevirmiş olduk
	vp.delta_u = vec_scale(vp.view_u, 1.0 / WIDTH); // * her bir pikselin genişliği 
	vp.delta_v = vec_scale(vp.view_v, 1.0 / HEIGHT); // * her bir pikselin yüksekliği 
	vp.upper_left = vec_sub(vp.camera_center, new_vector(0, 0, vp.focal_length)); // * kamera merkezinden focal length kadar geri gidildi z ekseninde 
	vp.upper_left = vec_sub(vp.upper_left, vec_scale(vp.view_u, 0.5)); // * viewportun yarısı kadar sola gidildi  
	vp.upper_left = vec_sub(vp.upper_left, vec_scale(vp.view_v, 0.5)); // * viewportun yarısı kadar yukarı gidildi
	vp.pixel00_loc = vec_sum(vp.upper_left,
			vec_scale(vec_sum(vp.delta_u, vp.delta_v), 0.5)); // * pikselin tam ortasını bulmak için delta_u ve delta_v nin yarısı kadar kaydırıldı 
	return (vp);
}

void	render_scene(t_vars *vars, t_list *world)
{
	int			x;
	int			y;
	t_viewport	vp;
	t_vector3	pixel_center;
	t_ray		r;

	vp = setup_viewport();
	y = 0;
	while (y < HEIGHT)
	{
		x = 0;
		while (x < WIDTH)
		{
			pixel_center = vec_sum(vp.pixel00_loc, vec_sum(vec_scale(vp.delta_u,
							x), vec_scale(vp.delta_v, y)));
			r.origin = vp.camera_center;
			r.direction = vec_sub(pixel_center, vp.camera_center);
			*(unsigned int *)(vars->addr + y * vars->size_line + x
					* (vars->bpp / 8)) = ray_color(r, world);
			x++;
		}
		y++;
	}
}
