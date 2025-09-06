#ifndef VECTOR_H
# define VECTOR_H

# include "Libft/libft.h"
# include "collector/collector.h"

typedef struct s_vector3
{
    double   x;
    double   y;
    double   z;
}t_vector3;

t_vector3 *vec_sum(t_vector3 *v1, t_vector3 *v2);
// t_vector3 *vec_sub(t_vector3 *v1, t_vector3 *v2);
// t_vector3 *vec_scale(t_vector3 *v1, double *k);
// double *vec_dot(t_vector3 *v1, t_vector3 *v2);
// t_vector3 *vec_cross(t_vector3 *v1, t_vector3 *v2);
// double *vec_len(t_vector3 *v1);
// t_vector3 *vec_normalize(t_vector3 *v1);

#endif