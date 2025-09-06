#include "minirt.h"

int main(int ac, char const **av)
{
        printf("\n");
        (void)ac;
        (void)av;

        t_vector3       v1;
        t_vector3       v2;
        t_vector3       *sum;

        v1.x = 1.234;
        v1.y = 2.345;
        v1.z = 3.456;

        v2.x = 4.567;
        v2.y = 5.678;
        v2.z = 6.789;
        sum = vec_sum(&v1, &v2);
        printf("x: %.2f y: %.2f z: %.2f\n", sum->x, sum->y, sum->z);
        ft_free();
        printf("\n");
        return 0;
}
