/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: musisman <musisman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/19 16:05:56 by musisman          #+#    #+#             */
/*   Updated: 2025/10/19 16:05:56 by musisman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_list	*world_objects(void)  // TODO parserdan gelecek t_objects_list structu olacak
{
	t_list	*world;

	world = NULL;
	// --- Among Us Karakteri ---

	// 1. Gövde (Kırmızı Kapsül = Silindir + 2 Küre)
	// Ana gövdeyi oluşturur. Y ekseninde dikey olarak duruyor. Kapsül görünümü için alt ve üstüne küreler eklenmiştir.
	ft_lstadd_back(&world, ft_lstnew(new_cylinder(
		new_vector(0, -0.1, -1.5),    // Konum (Biraz aşağıda ve kameradan uzakta)
		new_vector(0, 1, 0),      // Yön (Dikey)
		(double[2]){0.6, 0.5},    // Çap ve Yükseklik (Yükseklik azaltıldı)
		new_vector(1, 0, 0)       // Renk (Kırmızı)
	)));
	// Gövde Üst Küresi
	ft_lstadd_back(&world, ft_lstnew(new_sphere(new_vector(0, 0.15, -1.5), 0.3))); // Silindirin üst ucu
	// Gövde Alt Küresi
	ft_lstadd_back(&world, ft_lstnew(new_sphere(new_vector(0, -0.35, -1.5), 0.3))); // Silindirin alt ucu

	// 2. Vizör (Yana ve içeriye kaydırılmış Mavi Küre)
	// Gövdenin önüne ve yanına, göz hizasına bir küre yerleştiriyoruz.
	// Not: camera.c'deki `l_data.obj_col` rengi override ediyorsa, vizör de kırmızı görünebilir.
	// Gerçek rengi görmek için orayı nesnenin kendi rengini alacak şekilde düzenlemelisiniz.
	ft_lstadd_back(&world, ft_lstnew(new_sphere(new_vector(0.15, 0.1, -1.3), 0.2)));

	// 3. Bacaklar (İki adet daha uzun kırmızı kapsül)
	// Sol Bacak
	ft_lstadd_back(&world, ft_lstnew(new_cylinder(new_vector(-0.15, -0.55, -1.5), new_vector(0, 1, 0), (double[2]){0.25, 0.4}, new_vector(1, 0, 0))));
	ft_lstadd_back(&world, ft_lstnew(new_sphere(new_vector(-0.15, -0.75, -1.5), 0.125))); // Sol bacak alt küre
	// Sağ Bacak
	ft_lstadd_back(&world, ft_lstnew(new_cylinder(new_vector(0.15, -0.55, -1.5), new_vector(0, 1, 0), (double[2]){0.25, 0.4}, new_vector(1, 0, 0))));
	ft_lstadd_back(&world, ft_lstnew(new_sphere(new_vector(0.15, -0.75, -1.5), 0.125))); // Sağ bacak alt küre

	// Zemin Düzlemi (Mavi)
	ft_lstadd_back(&world, ft_lstnew(new_plane(new_vector(0, -0.9, 0), new_vector(0, 1, 0), new_vector(0, 0, 1))));
	// Açılı Arka Duvar Düzlemi (Gri) - Gölgenin düşeceği yer
	ft_lstadd_back(&world, ft_lstnew(new_plane(new_vector(0, 0, -2.7), new_vector(0.5, 0, 1), new_vector(0.5, 0.5, 0.5))));

	
	return (world);
}

// TODO ileride parserdan gelen veriyi buna benzer bir fonksiyon ile işleyeceğiz ki direkt t_list olarak world e ekleyebilelim
// // Bu fonksiyon parser'dan gelen ham veriyi, senin render sistemine çevirir
// void convert_and_add_to_world(t_list **world, t_obje_list *parser_list)
// {
//     t_object *new_obj;

//     while (parser_list)
//     {
//         if (parser_list->type == SPHERE)
//         {
//             // Arkadaşının struct'ından veriyi al, senin fonksiyonuna ver
//             new_obj = new_sphere(parser_list->objects.sphere.pos, 
//                                  parser_list->objects.sphere.diameter);
//             // Senin dünyana ekle
//             ft_lstadd_back(world, ft_lstnew(new_obj));
//         }
//         else if (parser_list->type == PLANE)
//         {
//             // new_plane(...)
//         }
//         parser_list = parser_list->next;
//     }
// }
// TODO *************************************************************************

static bool	mlx_process(t_list *world)
{
	t_cam_status	cam;
	t_vars			vars;

	vars.mlx = mlx_init(); // * mlx instance oluşturuldu
	if (!vars.mlx)
		return (false);
	vars.win = mlx_new_window(vars.mlx, WIDTH, HEIGHT, "miniRT"); // * window oluşturuldu
	if (!vars.win)
		return (false);
	vars.img = mlx_new_image(vars.mlx, WIDTH, HEIGHT); // * image oluşturuldu
	if (!vars.img)
		return (mlx_destroy_window(vars.mlx, vars.win), false); // * image oluşturulamazsa window silindi ve false döndürüldü
	vars.addr = mlx_get_data_addr(vars.img, &vars.bpp, &vars.size_line, &vars.endian); // * image data adresi alındı burada endianess da alındı ama kullanılmıyor şimdilik 
							// * sistem mimarisine göre ayarlanıyor eğer little endian ise 0 BRGBA formatında, big endian ise 1 ABGR formatında oluyor 
							// * ama biz zaten RGBA formatında çalışıyoruz sadece fonksiyona parametre olarak verildi ileride kullanılabilir mi bilmem 
	camera_render(&cam, world, &vars); // * sahne renderlandı
	mlx_put_image_to_window(vars.mlx, vars.win, vars.img, 0, 0); // * image windowa çizildi
	mlx_key_hook(vars.win, key_hook, &vars); // * key hook eklendi bu fonksiyon pencere açıkken klavye girişlerini dinler ve belirli bir tuşa basıldığında belirli bir fonksiyonu çağırır
	mlx_hook(vars.win, 17, 0, exit_func, &vars); // * pencere kapatma butonuna tıklanınca exit_func fonksiyonu çağrılır
	mlx_loop(vars.mlx); // * mlx döngüsü başlatıldı bu fonksiyon, pencere açık olduğu sürece sürekli olarak çalışır ve olayları dinler
	return (true);
}

int	main(void)
{
	// srand(time(NULL)); // TODO rastgele sayı üreteci başlatıldı şimdilik sabit değerlerle çalışıyoruz ileride açılacak
	if (!mlx_process(world_objects())) // * world_objects fonksiyonu çağrıldı ve dönen liste mlx_process fonksiyonuna parametre olarak verildi // TODO parserdan gelecek şimdi sabit objeler var
		return (ft_free(), 1); // * mlx_process fonksiyonu false dönerse program sonlandırıldı ve bellekteki tüm dinamik olarak ayrılmış veriler serbest bırakıldı
	ft_free(); // * program sonlandırılmadan önce bellekteki tüm dinamik olarak ayrılmış veriler serbest bırakıldı
	return (0);
}

int	exit_func(t_vars *vars)
{
	if (vars->img)
		mlx_destroy_image(vars->mlx, vars->img); // * image silindi bu fonksiyon, oluşturulan görüntü verilerini serbest bırakır ve bellekte yer açar
	if (vars->win)
		mlx_destroy_window(vars->mlx, vars->win); // * window silindi bu fonksiyon, oluşturulan pencereyi kapatır ve bellekte yer açar
	if (vars->mlx)
	{
		mlx_destroy_display(vars->mlx); // * mlx display silindi bu fonksiyon, oluşturulan grafik ortamını serbest bırakır ve bellekte yer açar
		free(vars->mlx);
	}
	ft_free();
	exit(0);
}

int	key_hook(int keycode, t_vars *vars)
{
	if (keycode == 65307) // * ESC tuşu basıldıysa
		exit_func(vars); // * exit_func fonksiyonu çağrıldı
	return (0);
}
