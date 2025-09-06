#include "vector.h"

t_vector3 vec_sum(t_vector3 v1, t_vector3 v2)
{
    t_vector3 sum;

    sum = {v1.x + v2.x, v1.y + v2.y, v1.z + v2.z};
    return  (sum);
}

t_vector3 vec_sub(t_vector3 v1, t_vector3 v2);
t_vector3 vec_scale(t_vector3 v1, float k);
float vec_dot(t_vector3 v1, t_vector3 v2);
t_vector3 vec_cross(t_vector3 v1, t_vector3 v2);
float vec_len(t_vector3 v1);
t_vector3 vec_normalize(t_vector3 v1);