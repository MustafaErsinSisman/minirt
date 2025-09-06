#ifndef VECTOR_H
# define VECTOR_H

typedef struct s_vector3
{
    float   x;
    float   y;
    float   z;
}t_vector3;

t_vector3 vec_sum(t_vector3 v1, t_vector3 v2);
t_vector3 vec_sub(t_vector3 v1, t_vector3 v2);
t_vector3 vec_scale(t_vector3 v1, float k);
float vec_dot(t_vector3 v1, t_vector3 v2);
t_vector3 vec_cross(t_vector3 v1, t_vector3 v2);
float vec_len(t_vector3 v1);
t_vector3 vec_normalize(t_vector3 v1);



#endif