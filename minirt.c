#include "minirt.h"

int main(int ac, char const **av)
{
        (void)ac;
        (void)av;

        t_vector3       v1;
        t_vector3       v2;
        t_vector3       sum;

        v1.x = 1;
        v1.y = 2;
        v1.z = 3;

        v2.x = 4;
        v2.y = 5;
        v2.z = 6;

        sum = vec_sum(v1, v2);
        printf("x: %2f y: %2f z: %2f\n", sum.x, sum.y, sum.z);
        return 0;
}
