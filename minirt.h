#ifndef MINIRT_H
# define MINIRT_H

typedef struct s_ambient
{
	float	range;
	float	color_r;
	float	color_b;
	float	color_g;
}	t_ambient;

typedef struct s_camera
{
	float	pos_x;
	float	pos_y;
	float	pos_z;
	float	normal_x;
	float	normal_y;
	float	normal_z;
	float	fov;
}t_camera;

typedef struct s_light
{
	float	pos_x;
	float	pos_y;
	float	pos_z;
	float	range;
	// float	color_r;
	// float	color_b;
	// float	color_g;
}t_light;

typedef struct s_sphere
{
	float	pos_x;
	float	pos_y;
	float	pos_z;
	float	diameter;
	float	color_r;
	float	color_b;
	float	color_g;
}t_sphere;

typedef struct s_plane
{
	float	pos_x;
	float	pos_y;
	float	pos_z;
	float	normal_x;
	float	normal_y;
	float	normal_z;
	float	color_r;
	float	color_b;
	float	color_g;
}t_plane;

typedef struct s_cylinder
{
	float	pos_x;
	float	pos_y;
	float	pos_z;
	float	normal_x;
	float	normal_y;
	float	normal_z;
	float	diameter;
	float	height;
	float	color_r;
	float	color_b;
	float	color_g;
}t_cylinder;

typedef union u_objects
{
	t_ambient ambiant;
	t_camera camera;
	t_light light;
	t_sphere sphere;
	t_plane plane;
	t_cylinder cylinder;
}	t_objects;

typedef struct s_list
{
	int type; // 0 ambiant 1 camera 2 light 3 sphere 4 plane 5 cylinder
	t_objects objects;
	struct s_list *next;
};


#endif