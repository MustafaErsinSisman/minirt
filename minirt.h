#ifndef MINIRT_H
# define MINIRT_H

# include <stdio.h>

# include "vector.h"


// typedef struct s_ambient
// {
// 	double	range;
// 	double	color_r;
// 	double	color_b;
// 	double	color_g;
// }	t_ambient;

// typedef struct s_camera
// {
// 	double	pos_x;
// 	double	pos_y;
// 	double	pos_z;
// 	double	normal_x;
// 	double	normal_y;
// 	double	normal_z;
// 	double	fov;
// }t_camera;

// typedef struct s_light
// {
// 	double	pos_x;
// 	double	pos_y;
// 	double	pos_z;
// 	double	range;
// 	// double	color_r;
// 	// double	color_b;
// 	// double	color_g;
// }t_light;

// typedef struct s_sphere
// {
// 	double	pos_x;
// 	double	pos_y;
// 	double	pos_z;
// 	double	diameter;
// 	double	color_r;
// 	double	color_b;
// 	double	color_g;
// }t_sphere;

// typedef struct s_plane
// {
// 	double	pos_x;
// 	double	pos_y;
// 	double	pos_z;
// 	double	normal_x;
// 	double	normal_y;
// 	double	normal_z;
// 	double	color_r;
// 	double	color_b;
// 	double	color_g;
// }t_plane;

// typedef struct s_cylinder
// {
// 	double	pos_x;
// 	double	pos_y;
// 	double	pos_z;
// 	double	normal_x;
// 	double	normal_y;
// 	double	normal_z;
// 	double	diameter;
// 	double	height;
// 	double	color_r;
// 	double	color_b;
// 	double	color_g;
// }t_cylinder;

// typedef union u_objects
// {
// 	t_ambient ambiant;
// 	t_camera camera;
// 	t_light light;
// 	t_sphere sphere;
// 	t_plane plane;
// 	t_cylinder cylinder;
// }	t_objects;

// typedef enum e_type
// {
// 	AMBIANT,
// 	CAMERA,
// 	LIGHT,
// 	SPHERE,
// 	PLANE,
// 	CYLINDER
// }t_type;

// typedef struct s_list
// {
// 	t_type type; // 0 AMBIANT 1 CAMERA 2 LIGHT 3 SPHERE 4 PLANE 5 CYLINDER // union için gerekli ama union neden gerekli
// 	t_objects objects;
// 	struct s_list *next;
// };

#endif