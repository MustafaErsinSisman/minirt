/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: musisman <musisman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/19 16:19:23 by musisman          #+#    #+#             */
/*   Updated: 2025/10/19 16:19:23 by musisman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_ray	new_ray(t_vector3 origin, t_vector3 direction) // * yeni ışın oluşturma fonksiyonu
{
	t_ray	r;

	r.origin = origin;
	r.direction = direction;
	return (r);
}

t_vector3	ray_at(t_ray r, double t) // * ışının t parametresine göre nokta hesaplama fonksiyonu
{
	return (vec_sum(r.origin, vec_scale(r.direction, t))); // * ışının origin noktasından direction vektörünün t katı kadar ilerlenmiş nokta döndürüldü P(t) = A + t*B formülü kullanıldı burada A ışının origin noktası B ise ışının yön vektörüdür
}

unsigned int	color(int r, int g, int b) // * renk değeri oluşturma fonksiyonu
{
	return ((r << 16) | (g << 8) | b); // * renk değeri döndürüldü bit kaydırma işlemi ile RGB formatında birleştirildi bunun matematiği şu şekilde gelen int rgb değerleri 0-255 aralığında olmalı sonra bit kaydırma işlemi ile 24 bitlik bir unsigned int değeri oluşturuluyor en son gelen değer örneğin r=255, g=0, b=0 ise bu değer 0xFF0000 yani kırmızı renk olarak temsil ediliyor
}

static unsigned int	get_background_color(const t_ray *ray) // * arka plan rengi hesaplama fonksiyonu
{
	t_vector3	unit_direction;
	double		a;
	double		r;
	double		g;
	double		b;

	unit_direction = vec_normalize(ray->direction); // * ışının yön vektörü normalize edildi bu sayede birim vektör elde edildi ki yön bilgisi korunmuş oldu ve işlemler daha kolay yapılabilir
	a = 0.5 * (unit_direction.y + 1.0); // * y bileşenine göre 0-1 aralığında bir değer hesaplandı bu değer gökyüzünün yukarıdan aşağıya doğru renk geçişini simüle etmek için kullanılacak
	r = (1.0 - a) * 1.0 + a * 0.5; // * gökyüzü rengi hesaplandı burada renk geçişi için lineer interpolasyon yapıldı lineer interpolation formülü : (1 - t) * start + t * end burada t bizim a değişkenimiz start beyaz renk end ise açık mavi renk lineer interpolation anlamı şudur : iki renk arasında t parametresine göre geçiş yapar t 0 ise start rengi t 1 ise end rengi olur t 0 ile 1 arasında ise start ve end renkleri arasında bir renk elde edilir
	g = (1.0 - a) * 1.0 + a * 0.7; // * gökyüzü rengi hesaplandı buradaki değerler de açık mavi renk tonları
	b = (1.0 - a) * 1.0 + a * 1.0;
	return (color((int)(255.999 * r),
		(int)(255.999 * g), (int)(255.999 * b))); // * arka plan rengi döndürüldü
}

// * burada 255.999 ile çarpılmasının matematiğini detaylı anlatalım: 
// * rgb değerleri 0.0 ile 1.0 arasında float değerlerdir ve 
// * biz bu değerleri 0 ile 255 arasında unsigned int değerlerine dönüştürmek istiyoruz.
// * Normalde bunu yapmak için rgb değerini 255 ile çarparız ve sonucu int'e dönüştürürüz.
// * Ancak, eğer rgb değeri tam olarak 1.0 ise, 1.0 * 255 = 255.0 olur ve int'e dönüştürüldüğünde bu değer 255 olur. 
// * Fakat, bazı durumlarda floating point aritmetiği nedeniyle bu çarpma işlemi sonucunda elde edilen değer 
// * tam olarak 255.0 olmayabilir, örneğin 255.999999 gibi bir değer olabilir. 
// * Eğer bu değeri doğrudan int'e dönüştürürsek, sonuç 256 olur ki bu istenmeyen bir durumdur 
// * çünkü renk bileşenleri 0-255 aralığında olmalıdır. Bu nedenle, rgb değerini 255.999 ile çarparız. 
// * Bu sayede, rgb değeri 1.0 olduğunda bile sonuç 255.999 olur ve int'e dönüştürüldüğünde 
// * doğru şekilde 255 olarak kalır. Bu küçük fark, floating point hatalarını önlemeye yardımcı olur ve 
// * renk bileşenlerinin doğru aralıkta kalmasını sağlar.

unsigned int	ray_color(t_ray ray, t_list *world)
{
	t_hit_record	rec; // * hit kaydı
	t_hit_status	status; // * hit durumu
	double			r;
	double			g;
	double			b;

	status.ray = &ray; // * ışın bilgisi
	status.t_min = 0.001; // * minimum t değeri bu değer kameranın hemen önünde bir nokta belirler böylece yüzeye çok yakın noktalarda oluşabilecek görsel hatalar engellenir
	status.t_max = INFINITY; // * maximum t değeri bu değer sonsuz olarak ayarlandı böylece ışın sonsuza kadar devam edebilir
	status.rec = &rec; // * hit kaydı için bellek ayırma buradaki kayıtlar şu işe yarıyor : örneğin bir ışın birden fazla nesneye çarpabilir bu durumda en yakın çarpma noktasını bulmak için her çarpma testi sonucunda elde edilen bilgileri geçici bir kayıtta tutuyoruz ve en yakın çarpma noktasını bulduğumuzda bu bilgileri asıl kayda kopyalıyoruz böylece en yakın çarpma noktasına ait bilgileri saklamış oluyoruz
	if (hit_world(world, &status)) // TODO nesneye göre olmalı şu an karışık // * dünyadaki nesnelere çarpma testi yapıldı
	{
		r = 0.5 * (rec.normal.x + 1.0); // * normal vektörün x bileşenine göre renk hesaplandı
		g = 0.5 * (rec.normal.y + 1.0);	// * normal vektörün y bileşenine göre renk hesaplandı
		b = 0.5 * (rec.normal.z + 1.0);	// * normal vektörün z bileşenine göre renk hesaplandı
		return (color((int)(255.999 * r),
			(int)(255.999 * g), (int)(255.999 * b))); // * renk değeri döndürüldü
	} // * şu an sadece test için normal vektörün bileşenlerine göre renk hesaplanıyor ileride ışıklandırma eklenecek
	return (get_background_color(&ray)); // * arka plan rengi bu da şu an sadece test için gökyüzü rengi hesaplanıyor ileride arka plan .rt dosyasından gelecek
}
