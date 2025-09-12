/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yozlu <yozlu@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/07 16:01:24 by musisman          #+#    #+#             */
/*   Updated: 2025/09/12 17:51:57 by yozlu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

// int	main(int ac, char **av)
// {
// 	t_vector3	v1;
// 	t_vector3	v2;
// 	t_vector3	*res;
// 	double		*dot;

// 	printf("\n");
// 	(void)ac;
// 	(void)av;
// 	v1.x = 1;
// 	v1.y = 2;
// 	v1.z = 3;
// 	v2.x = 4;
// 	v2.y = 5;
// 	v2.z = 6;
// 	printf("v1: x: %.2f y: %.2f z: %.2f\n", v1.x, v1.y, v1.z);
// 	printf("v2: x: %.2f y: %.2f z: %.2f\n", v2.x, v2.y, v2.z);
// 	printf("\n");
// 	res = vec_sum(&v1, &v2);
// 	printf("sum: x: %.2f y: %.2f z: %.2f\n", res->x, res->y, res->z);
// 	res = vec_sub(&v1, &v2);
// 	printf("sub: x: %.2f y: %.2f z: %.2f\n", res->x, res->y, res->z);
// 	res = vec_scale(&v1, 5);
// 	printf("5x scale v1: x: %.2f y: %.2f z: %.2f\n", res->x, res->y, res->z);
// 	dot = vec_dot(&v1, &v2);
// 	printf("dot: %f \n", *dot);
// 	res = vec_cross(&v1, &v2);
// 	printf("cross: x: %.2f y: %.2f z: %.2f\n", res->x, res->y, res->z);
// 	dot = vec_len(&v1);
// 	printf("len v1: %f \n", *dot);
// 	res = vec_normalize(&v1);
// 	printf("normalize v1: x: %.2f y: %.2f z: %.2f\n", res->x, res->y, res->z);
// 	ft_free();
// 	printf("\n");
// 	return (0);
// }
