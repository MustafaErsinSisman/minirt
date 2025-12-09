/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: musisman <musisman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/28 18:15:40 by musisman          #+#    #+#             */
/*   Updated: 2025/11/28 18:15:40 by musisman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CYLINDER_H
# define CYLINDER_H

typedef struct s_cylinder
{
	t_vector3	pos;
	t_vector3	normal;
	double		diameter;
	double		radius;
	double		height;
	t_vector3	rgb;
}	t_cylinder;

typedef struct s_cy_vars
{
	double	t[2];
	double	t_final;
	int		type;
	bool	hit;
}	t_cy_vars;

t_object	*new_cylinder(t_vector3 pos, t_vector3 normal,
				double diameter_height[2], t_vector3 rgb);
bool		hit_cylinder(t_object *obj, t_hit_status *status);
bool		solve_cylinder_quadratic(t_cylinder *cy, const t_ray *r, double *t);
void		check_body_height(t_cylinder *cy, t_hit_status *st, t_cy_vars *v);
void		check_caps(t_cylinder *cy, t_hit_status *st, t_cy_vars *v);
bool		check_cap_intersection(t_cylinder *cy, const t_ray *ray,
				t_vector3 p_cap, double *t);
t_vector3	get_cylinder_normal(t_cylinder *cy, t_vector3 p);
#endif