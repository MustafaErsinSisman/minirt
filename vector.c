#include "vector.h"

#include <stdio.h> // !sil printf test için var

t_vector3   *vec_sum(t_vector3 *v1, t_vector3 *v2)
{
    t_vector3   *sum;

    sum = malloc(sizeof(t_vector3));
    if (!sum)
        return NULL;
        
    sum->x = v1->x + v2->x;
    sum->y = v1->y + v2->y;
    sum->z = v1->z + v2->z;
    return  (sum);
}

// t_vector3 *vec_sub(t_vector3 *v1, t_vector3 *v2)
// {
//     t_vector3 *sub;

//     return (sub);
// }
// t_vector3 *vec_scale(t_vector3 *v1, double k)
// {
//     t_vector3 *scale;

//     return (scale);
// }
// double *vec_dot(t_vector3 *v1, t_vector3 *v2)
// {
//     double *dot;

//     return (dot);
// }
// t_vector3 *vec_cross(t_vector3 *v1, t_vector3 *v2)
// {
//     t_vector3 *cross;

//     return (cross);
// }
// double *vec_len(t_vector3 *v1)
// {
//     double *len;

//     return (len);
// }
// t_vector3 *vec_normalize(t_vector3 *v1)
// {
//     t_vector3 *normal;

//     return (normal);
// }