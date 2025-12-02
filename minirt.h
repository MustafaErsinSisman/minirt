/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: musisman <musisman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/07 16:06:18 by musisman          #+#    #+#             */
/*   Updated: 2025/12/02 15:54:28 by musisman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_H
# define MINIRT_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>

# include "minilibx-linux/mlx.h"
# include "objects/objects.h"

# define WIDTH 800.0
# define HEIGHT 450.0

// * dereceyi radyana çevirme fonksiyonu 
// * buradaki inline ifadesi derleyiciye bu fonksiyonu çağıran yere 
// * direkt olarak kodu yerleştirmesini söyler böylece fonksiyon çağrısı overhead i ortadan kalkar ve
// * performans artar
// * overhead: normalde bir fonksiyon çağrısı yapıldığında program akışı 
// * fonksiyonun bulunduğu adrese gider orada fonksiyonun kodu çalıştırılır ve 
// * sonra tekrar çağıran yere geri dönülür bu süreç zaman alır 
// * özellikle sıkça çağrılan küçük fonksiyonlarda bu zaman kaybı performansı olumsuz etkileyebilir 
// * inline fonksiyonlarda ise derleyici fonksiyon çağrısını kaldırır ve
// * fonksiyonun kodunu çağıran yere direkt olarak yerleştirir 
// * böylece fonksiyon çağrısına bağlı zaman kaybı ortadan kalkar

static inline double	degrees_to_radians(double degrees)
{
	return (degrees * M_PI / 180.0); // * dereceyi radyana çevirme formülü
}

// * 0.0 (dahil) ile 1.0 (hariç) arasında rastgele double üretir. [0, 1) bunu şurada kullanıyoruz: her piksel için rastgele bir nokta seçmek istediğimizde
static inline double random_double(void)
{
    // RAND_MAX + 1.0 yaparak sonucun asla 1.0 olmamasını garantiliyoruz (< 1.0)
    return (rand() / (RAND_MAX + 1.0));
}

// * Belirtilen min ve max değerleri arasında rastgele double üretir. [min, max) bunu şurada kullanıyoruz: her piksel için rastgele bir nokta seçmek istediğimizde
static inline double random_double_range(double min, double max)
{
    return (min + (max - min) * random_double());
}

static inline double clamp(double x, double min, double max) // * x değerini min ve max arasında sınırlama fonksiyonu bunu şurada kullanıyoruz: renk değerlerini 0-255 aralığında tutmak istediğimizde
{
	if (x < min)
		return (min);
	if (x > max)
		return (max);
	return (x);
}

typedef struct s_vars
{
	void	*mlx; // * mlx instance
	void	*win; // * window instance
	void	*img; // * image instance
	char	*addr; // * image data address
	int		bpp; // * bits per pixel
	int		size_line; // * size of a line in bytes
	int		endian; // * endianess
}	t_vars;

int					exit_func(t_vars *vars);
int					key_hook(int keycode, t_vars *vars);
t_ray				new_ray(t_vector3 origin, t_vector3 direction);
t_vector3			ray_at(t_ray r, double t);
t_ray				get_ray(t_cam_status *cam, int i, int j);
unsigned int		color(int r, int g, int b);

#endif
