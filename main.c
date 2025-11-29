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
	ft_lstadd_back(&world, ft_lstnew(new_sphere(new_vector(0, 0, -1), 0.5)));
	ft_lstadd_back(&world, ft_lstnew(new_sphere(new_vector(0, -100.5, -1), 100.0)));

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
	t_vars	vars;
	t_cam_status    cam;

	vars.mlx = mlx_init(); // * mlx instance oluşturuldu
	if (!vars.mlx)
		return (false);
	cam.aspect_ratio = 16.0 / 9.0;
    	cam.image_width = 400;
	vars.win = mlx_new_window(vars.mlx, WIDTH, HEIGHT, "miniRT"); // * window oluşturuldu
	if (!vars.win)
		return (false);
	vars.img = mlx_new_image(vars.mlx, cam.image_width, (int)(cam.image_width / cam.aspect_ratio)); // * image oluşturuldu
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




	// ! CILGINLIK

	// ft_lstadd_back(&world, ft_lstnew(new_sphere(new_vector(0.1, 0, -1), 1.0)));
	// ft_lstadd_back(&world, ft_lstnew(new_sphere(new_vector(0.2, 0, -1), 1.0)));
	// ft_lstadd_back(&world, ft_lstnew(new_sphere(new_vector(0.3, 0, -1), 1.0)));
	// ft_lstadd_back(&world, ft_lstnew(new_sphere(new_vector(0.4, 0, -1), 1.0)));
	// ft_lstadd_back(&world, ft_lstnew(new_sphere(new_vector(0.5, 0, -1), 1.0)));
	// ft_lstadd_back(&world, ft_lstnew(new_sphere(new_vector(0.6, 0, -1), 1.0)));
	// ft_lstadd_back(&world, ft_lstnew(new_sphere(new_vector(0.7, 0, -1), 1.0)));
	// ft_lstadd_back(&world, ft_lstnew(new_sphere(new_vector(0.8, 0, -1), 1.0)));
	// ft_lstadd_back(&world, ft_lstnew(new_sphere(new_vector(0.9, 0, -1), 1.0)));
	// ft_lstadd_back(&world, ft_lstnew(new_sphere(new_vector(1.0, 0, -1), 1.0)));
	

	// ft_lstadd_back(&world, ft_lstnew(new_sphere(new_vector(-0.1, 0, -1), 1.0)));
	// ft_lstadd_back(&world, ft_lstnew(new_sphere(new_vector(-0.2, 0, -1), 1.0)));
	// ft_lstadd_back(&world, ft_lstnew(new_sphere(new_vector(-0.3, 0, -1), 1.0)));
	// ft_lstadd_back(&world, ft_lstnew(new_sphere(new_vector(-0.4, 0, -1), 1.0)));
	// ft_lstadd_back(&world, ft_lstnew(new_sphere(new_vector(-0.5, 0, -1), 1.0)));
	// ft_lstadd_back(&world, ft_lstnew(new_sphere(new_vector(-0.6, 0, -1), 1.0)));
	// ft_lstadd_back(&world, ft_lstnew(new_sphere(new_vector(-0.7, 0, -1), 1.0)));
	// ft_lstadd_back(&world, ft_lstnew(new_sphere(new_vector(-0.8, 0, -1), 1.0)));
	// ft_lstadd_back(&world, ft_lstnew(new_sphere(new_vector(-0.9, 0, -1), 1.0)));
	// ft_lstadd_back(&world, ft_lstnew(new_sphere(new_vector(-1.0, 0, -1), 1.0)));


	// ft_lstadd_back(&world, ft_lstnew(new_sphere(new_vector(0, 0.1, -1), 1.0)));

	// ft_lstadd_back(&world, ft_lstnew(new_sphere(new_vector(0.1, 0.1, -1), 1.0)));
	// ft_lstadd_back(&world, ft_lstnew(new_sphere(new_vector(0.2, 0.1, -1), 1.0)));
	// ft_lstadd_back(&world, ft_lstnew(new_sphere(new_vector(0.3, 0.1, -1), 1.0)));
	// ft_lstadd_back(&world, ft_lstnew(new_sphere(new_vector(0.4, 0.1, -1), 1.0)));
	// ft_lstadd_back(&world, ft_lstnew(new_sphere(new_vector(0.5, 0.1, -1), 1.0)));
	// ft_lstadd_back(&world, ft_lstnew(new_sphere(new_vector(0.6, 0.1, -1), 1.0)));
	// ft_lstadd_back(&world, ft_lstnew(new_sphere(new_vector(0.7, 0.1, -1), 1.0)));
	// ft_lstadd_back(&world, ft_lstnew(new_sphere(new_vector(0.8, 0.1, -1), 1.0)));
	// ft_lstadd_back(&world, ft_lstnew(new_sphere(new_vector(0.9, 0.1, -1), 1.0)));
	// ft_lstadd_back(&world, ft_lstnew(new_sphere(new_vector(1.0, 0.1, -1), 1.0)));
	// ft_lstadd_back(&world, ft_lstnew(new_sphere(new_vector(-0.1, 0.1, -1), 1.0)));
	// ft_lstadd_back(&world, ft_lstnew(new_sphere(new_vector(-0.2, 0.1, -1), 1.0)));
	// ft_lstadd_back(&world, ft_lstnew(new_sphere(new_vector(-0.3, 0.1, -1), 1.0)));
	// ft_lstadd_back(&world, ft_lstnew(new_sphere(new_vector(-0.4, 0.1, -1), 1.0)));
	// ft_lstadd_back(&world, ft_lstnew(new_sphere(new_vector(-0.5, 0.1, -1), 1.0)));
	// ft_lstadd_back(&world, ft_lstnew(new_sphere(new_vector(-0.6, 0.1, -1), 1.0)));
	// ft_lstadd_back(&world, ft_lstnew(new_sphere(new_vector(-0.7, 0.1, -1), 1.0)));
	// ft_lstadd_back(&world, ft_lstnew(new_sphere(new_vector(-0.8, 0.1, -1), 1.0)));
	// ft_lstadd_back(&world, ft_lstnew(new_sphere(new_vector(-0.9, 0.1, -1), 1.0)));
	// ft_lstadd_back(&world, ft_lstnew(new_sphere(new_vector(-1.0, 0.1, -1), 1.0)));
	

	// ft_lstadd_back(&world, ft_lstnew(new_sphere(new_vector(0, 0.2, -1), 1.0)));

	// ft_lstadd_back(&world, ft_lstnew(new_sphere(new_vector(0.1, 0.2, -1), 1.0)));
	// ft_lstadd_back(&world, ft_lstnew(new_sphere(new_vector(0.2, 0.2, -1), 1.0)));
	// ft_lstadd_back(&world, ft_lstnew(new_sphere(new_vector(0.3, 0.2, -1), 1.0)));
	// ft_lstadd_back(&world, ft_lstnew(new_sphere(new_vector(0.4, 0.2, -1), 1.0)));
	// ft_lstadd_back(&world, ft_lstnew(new_sphere(new_vector(0.5, 0.2, -1), 1.0)));
	// ft_lstadd_back(&world, ft_lstnew(new_sphere(new_vector(0.6, 0.2, -1), 1.0)));
	// ft_lstadd_back(&world, ft_lstnew(new_sphere(new_vector(0.7, 0.2, -1), 1.0)));
	// ft_lstadd_back(&world, ft_lstnew(new_sphere(new_vector(0.8, 0.2, -1), 1.0)));
	// ft_lstadd_back(&world, ft_lstnew(new_sphere(new_vector(0.9, 0.2, -1), 1.0)));
	// ft_lstadd_back(&world, ft_lstnew(new_sphere(new_vector(1.0, 0.2, -1), 1.0)));
	// ft_lstadd_back(&world, ft_lstnew(new_sphere(new_vector(-0.1, 0.2, -1), 1.0)));
	// ft_lstadd_back(&world, ft_lstnew(new_sphere(new_vector(-0.2, 0.2, -1), 1.0)));
	// ft_lstadd_back(&world, ft_lstnew(new_sphere(new_vector(-0.3, 0.2, -1), 1.0)));
	// ft_lstadd_back(&world, ft_lstnew(new_sphere(new_vector(-0.4, 0.2, -1), 1.0)));
	// ft_lstadd_back(&world, ft_lstnew(new_sphere(new_vector(-0.5, 0.2, -1), 1.0)));
	// ft_lstadd_back(&world, ft_lstnew(new_sphere(new_vector(-0.6, 0.2, -1), 1.0)));
	// ft_lstadd_back(&world, ft_lstnew(new_sphere(new_vector(-0.7, 0.2, -1), 1.0)));
	// ft_lstadd_back(&world, ft_lstnew(new_sphere(new_vector(-0.8, 0.2, -1), 1.0)));
	// ft_lstadd_back(&world, ft_lstnew(new_sphere(new_vector(-0.9, 0.2, -1), 1.0)));
	// ft_lstadd_back(&world, ft_lstnew(new_sphere(new_vector(-1.0, 0.2, -1), 1.0)));


	// ft_lstadd_back(&world, ft_lstnew(new_sphere(new_vector(0, 0.3, -1), 1.0)));

	// ft_lstadd_back(&world, ft_lstnew(new_sphere(new_vector(0.1, 0.3, -1), 1.0)));
	// ft_lstadd_back(&world, ft_lstnew(new_sphere(new_vector(0.2, 0.3, -1), 1.0)));
	// ft_lstadd_back(&world, ft_lstnew(new_sphere(new_vector(0.3, 0.3, -1), 1.0)));
	// ft_lstadd_back(&world, ft_lstnew(new_sphere(new_vector(0.4, 0.3, -1), 1.0)));
	// ft_lstadd_back(&world, ft_lstnew(new_sphere(new_vector(0.5, 0.3, -1), 1.0)));
	// ft_lstadd_back(&world, ft_lstnew(new_sphere(new_vector(0.6, 0.3, -1), 1.0)));
	// ft_lstadd_back(&world, ft_lstnew(new_sphere(new_vector(0.7, 0.3, -1), 1.0)));
	// ft_lstadd_back(&world, ft_lstnew(new_sphere(new_vector(0.8, 0.3, -1), 1.0)));
	// ft_lstadd_back(&world, ft_lstnew(new_sphere(new_vector(0.9, 0.3, -1), 1.0)));
	// ft_lstadd_back(&world, ft_lstnew(new_sphere(new_vector(1.0, 0.3, -1), 1.0)));
	// ft_lstadd_back(&world, ft_lstnew(new_sphere(new_vector(-0.1, 0.3, -1), 1.0)));
	// ft_lstadd_back(&world, ft_lstnew(new_sphere(new_vector(-0.2, 0.3, -1), 1.0)));
	// ft_lstadd_back(&world, ft_lstnew(new_sphere(new_vector(-0.3, 0.3, -1), 1.0)));
	// ft_lstadd_back(&world, ft_lstnew(new_sphere(new_vector(-0.4, 0.3, -1), 1.0)));
	// ft_lstadd_back(&world, ft_lstnew(new_sphere(new_vector(-0.5, 0.3, -1), 1.0)));
	// ft_lstadd_back(&world, ft_lstnew(new_sphere(new_vector(-0.6, 0.3, -1), 1.0)));
	// ft_lstadd_back(&world, ft_lstnew(new_sphere(new_vector(-0.7, 0.3, -1), 1.0)));
	// ft_lstadd_back(&world, ft_lstnew(new_sphere(new_vector(-0.8, 0.3, -1), 1.0)));
	// ft_lstadd_back(&world, ft_lstnew(new_sphere(new_vector(-0.9, 0.3, -1), 1.0)));
	// ft_lstadd_back(&world, ft_lstnew(new_sphere(new_vector(-1.0, 0.3, -1), 1.0)));


	// ft_lstadd_back(&world, ft_lstnew(new_sphere(new_vector(0, 0.4, -1), 1.0)));

	// ft_lstadd_back(&world, ft_lstnew(new_sphere(new_vector(0.1, 0.4, -1), 1.0)));
	// ft_lstadd_back(&world, ft_lstnew(new_sphere(new_vector(0.2, 0.4, -1), 1.0)));
	// ft_lstadd_back(&world, ft_lstnew(new_sphere(new_vector(0.3, 0.4, -1), 1.0)));
	// ft_lstadd_back(&world, ft_lstnew(new_sphere(new_vector(0.4, 0.4, -1), 1.0)));
	// ft_lstadd_back(&world, ft_lstnew(new_sphere(new_vector(0.5, 0.4, -1), 1.0)));
	// ft_lstadd_back(&world, ft_lstnew(new_sphere(new_vector(0.6, 0.4, -1), 1.0)));
	// ft_lstadd_back(&world, ft_lstnew(new_sphere(new_vector(0.7, 0.4, -1), 1.0)));
	// ft_lstadd_back(&world, ft_lstnew(new_sphere(new_vector(0.8, 0.4, -1), 1.0)));
	// ft_lstadd_back(&world, ft_lstnew(new_sphere(new_vector(0.9, 0.4, -1), 1.0)));
	// ft_lstadd_back(&world, ft_lstnew(new_sphere(new_vector(1.0, 0.4, -1), 1.0)));
	// ft_lstadd_back(&world, ft_lstnew(new_sphere(new_vector(-0.1, 0.4, -1), 1.0)));
	// ft_lstadd_back(&world, ft_lstnew(new_sphere(new_vector(-0.2, 0.4, -1), 1.0)));
	// ft_lstadd_back(&world, ft_lstnew(new_sphere(new_vector(-0.3, 0.4, -1), 1.0)));
	// ft_lstadd_back(&world, ft_lstnew(new_sphere(new_vector(-0.4, 0.4, -1), 1.0)));
	// ft_lstadd_back(&world, ft_lstnew(new_sphere(new_vector(-0.5, 0.4, -1), 1.0)));
	// ft_lstadd_back(&world, ft_lstnew(new_sphere(new_vector(-0.6, 0.4, -1), 1.0)));
	// ft_lstadd_back(&world, ft_lstnew(new_sphere(new_vector(-0.7, 0.4, -1), 1.0)));
	// ft_lstadd_back(&world, ft_lstnew(new_sphere(new_vector(-0.8, 0.4, -1), 1.0)));
	// ft_lstadd_back(&world, ft_lstnew(new_sphere(new_vector(-0.9, 0.4, -1), 1.0)));
	// ft_lstadd_back(&world, ft_lstnew(new_sphere(new_vector(-1.0, 0.4, -1), 1.0)));


	// ft_lstadd_back(&world, ft_lstnew(new_sphere(new_vector(0, 0.5, -1), 1.0)));

	// ft_lstadd_back(&world, ft_lstnew(new_sphere(new_vector(0.1, 0.5, -1), 1.0)));
	// ft_lstadd_back(&world, ft_lstnew(new_sphere(new_vector(0.2, 0.5, -1), 1.0)));
	// ft_lstadd_back(&world, ft_lstnew(new_sphere(new_vector(0.3, 0.5, -1), 1.0)));
	// ft_lstadd_back(&world, ft_lstnew(new_sphere(new_vector(0.4, 0.5, -1), 1.0)));
	// ft_lstadd_back(&world, ft_lstnew(new_sphere(new_vector(0.5, 0.5, -1), 1.0)));
	// ft_lstadd_back(&world, ft_lstnew(new_sphere(new_vector(0.6, 0.5, -1), 1.0)));
	// ft_lstadd_back(&world, ft_lstnew(new_sphere(new_vector(0.7, 0.5, -1), 1.0)));
	// ft_lstadd_back(&world, ft_lstnew(new_sphere(new_vector(0.8, 0.5, -1), 1.0)));
	// ft_lstadd_back(&world, ft_lstnew(new_sphere(new_vector(0.9, 0.5, -1), 1.0)));
	// ft_lstadd_back(&world, ft_lstnew(new_sphere(new_vector(1.0, 0.5, -1), 1.0)));
	// ft_lstadd_back(&world, ft_lstnew(new_sphere(new_vector(-0.1, 0.5, -1), 1.0)));
	// ft_lstadd_back(&world, ft_lstnew(new_sphere(new_vector(-0.2, 0.5, -1), 1.0)));
	// ft_lstadd_back(&world, ft_lstnew(new_sphere(new_vector(-0.3, 0.5, -1), 1.0)));
	// ft_lstadd_back(&world, ft_lstnew(new_sphere(new_vector(-0.4, 0.5, -1), 1.0)));
	// ft_lstadd_back(&world, ft_lstnew(new_sphere(new_vector(-0.5, 0.5, -1), 1.0)));
	// ft_lstadd_back(&world, ft_lstnew(new_sphere(new_vector(-0.6, 0.5, -1), 1.0)));
	// ft_lstadd_back(&world, ft_lstnew(new_sphere(new_vector(-0.7, 0.5, -1), 1.0)));
	// ft_lstadd_back(&world, ft_lstnew(new_sphere(new_vector(-0.8, 0.5, -1), 1.0)));
	// ft_lstadd_back(&world, ft_lstnew(new_sphere(new_vector(-0.9, 0.5, -1), 1.0)));
	// ft_lstadd_back(&world, ft_lstnew(new_sphere(new_vector(-1.0, 0.5, -1), 1.0)));


	// ft_lstadd_back(&world, ft_lstnew(new_sphere(new_vector(0, -0.1, -1), 1.0)));

	// ft_lstadd_back(&world, ft_lstnew(new_sphere(new_vector(0.1, -0.1, -1), 1.0)));
	// ft_lstadd_back(&world, ft_lstnew(new_sphere(new_vector(0.2, -0.1, -1), 1.0)));
	// ft_lstadd_back(&world, ft_lstnew(new_sphere(new_vector(0.3, -0.1, -1), 1.0)));
	// ft_lstadd_back(&world, ft_lstnew(new_sphere(new_vector(0.4, -0.1, -1), 1.0)));
	// ft_lstadd_back(&world, ft_lstnew(new_sphere(new_vector(0.5, -0.1, -1), 1.0)));
	// ft_lstadd_back(&world, ft_lstnew(new_sphere(new_vector(0.6, -0.1, -1), 1.0)));
	// ft_lstadd_back(&world, ft_lstnew(new_sphere(new_vector(0.7, -0.1, -1), 1.0)));
	// ft_lstadd_back(&world, ft_lstnew(new_sphere(new_vector(0.8, -0.1, -1), 1.0)));
	// ft_lstadd_back(&world, ft_lstnew(new_sphere(new_vector(0.9, -0.1, -1), 1.0)));
	// ft_lstadd_back(&world, ft_lstnew(new_sphere(new_vector(1.0, -0.1, -1), 1.0)));
	// ft_lstadd_back(&world, ft_lstnew(new_sphere(new_vector(-0.1, -0.1, -1), 1.0)));
	// ft_lstadd_back(&world, ft_lstnew(new_sphere(new_vector(-0.2, -0.1, -1), 1.0)));
	// ft_lstadd_back(&world, ft_lstnew(new_sphere(new_vector(-0.3, -0.1, -1), 1.0)));
	// ft_lstadd_back(&world, ft_lstnew(new_sphere(new_vector(-0.4, -0.1, -1), 1.0)));
	// ft_lstadd_back(&world, ft_lstnew(new_sphere(new_vector(-0.5, -0.1, -1), 1.0)));
	// ft_lstadd_back(&world, ft_lstnew(new_sphere(new_vector(-0.6, -0.1, -1), 1.0)));
	// ft_lstadd_back(&world, ft_lstnew(new_sphere(new_vector(-0.7, -0.1, -1), 1.0)));
	// ft_lstadd_back(&world, ft_lstnew(new_sphere(new_vector(-0.8, -0.1, -1), 1.0)));
	// ft_lstadd_back(&world, ft_lstnew(new_sphere(new_vector(-0.9, -0.1, -1), 1.0)));
	// ft_lstadd_back(&world, ft_lstnew(new_sphere(new_vector(-1.0, -0.1, -1), 1.0)));


	// ft_lstadd_back(&world, ft_lstnew(new_sphere(new_vector(0, -0.2, -1), 1.0)));

	// ft_lstadd_back(&world, ft_lstnew(new_sphere(new_vector(0.1, -0.2, -1), 1.0)));
	// ft_lstadd_back(&world, ft_lstnew(new_sphere(new_vector(0.2, -0.2, -1), 1.0)));
	// ft_lstadd_back(&world, ft_lstnew(new_sphere(new_vector(0.3, -0.2, -1), 1.0)));
	// ft_lstadd_back(&world, ft_lstnew(new_sphere(new_vector(0.4, -0.2, -1), 1.0)));
	// ft_lstadd_back(&world, ft_lstnew(new_sphere(new_vector(0.5, -0.2, -1), 1.0)));
	// ft_lstadd_back(&world, ft_lstnew(new_sphere(new_vector(0.6, -0.2, -1), 1.0)));
	// ft_lstadd_back(&world, ft_lstnew(new_sphere(new_vector(0.7, -0.2, -1), 1.0)));
	// ft_lstadd_back(&world, ft_lstnew(new_sphere(new_vector(0.8, -0.2, -1), 1.0)));
	// ft_lstadd_back(&world, ft_lstnew(new_sphere(new_vector(0.9, -0.2, -1), 1.0)));
	// ft_lstadd_back(&world, ft_lstnew(new_sphere(new_vector(1.0, -0.2, -1), 1.0)));
	// ft_lstadd_back(&world, ft_lstnew(new_sphere(new_vector(-0.1, -0.2, -1), 1.0)));
	// ft_lstadd_back(&world, ft_lstnew(new_sphere(new_vector(-0.2, -0.2, -1), 1.0)));
	// ft_lstadd_back(&world, ft_lstnew(new_sphere(new_vector(-0.3, -0.2, -1), 1.0)));
	// ft_lstadd_back(&world, ft_lstnew(new_sphere(new_vector(-0.4, -0.2, -1), 1.0)));
	// ft_lstadd_back(&world, ft_lstnew(new_sphere(new_vector(-0.5, -0.2, -1), 1.0)));
	// ft_lstadd_back(&world, ft_lstnew(new_sphere(new_vector(-0.6, -0.2, -1), 1.0)));
	// ft_lstadd_back(&world, ft_lstnew(new_sphere(new_vector(-0.7, -0.2, -1), 1.0)));
	// ft_lstadd_back(&world, ft_lstnew(new_sphere(new_vector(-0.8, -0.2, -1), 1.0)));
	// ft_lstadd_back(&world, ft_lstnew(new_sphere(new_vector(-0.9, -0.2, -1), 1.0)));
	// ft_lstadd_back(&world, ft_lstnew(new_sphere(new_vector(-1.0, -0.2, -1), 1.0)));


	// ft_lstadd_back(&world, ft_lstnew(new_sphere(new_vector(0, -0.3, -1), 1.0)));

	// ft_lstadd_back(&world, ft_lstnew(new_sphere(new_vector(0.1, -0.3, -1), 1.0)));
	// ft_lstadd_back(&world, ft_lstnew(new_sphere(new_vector(0.2, -0.3, -1), 1.0)));
	// ft_lstadd_back(&world, ft_lstnew(new_sphere(new_vector(0.3, -0.3, -1), 1.0)));
	// ft_lstadd_back(&world, ft_lstnew(new_sphere(new_vector(0.4, -0.3, -1), 1.0)));
	// ft_lstadd_back(&world, ft_lstnew(new_sphere(new_vector(0.5, -0.3, -1), 1.0)));
	// ft_lstadd_back(&world, ft_lstnew(new_sphere(new_vector(0.6, -0.3, -1), 1.0)));
	// ft_lstadd_back(&world, ft_lstnew(new_sphere(new_vector(0.7, -0.3, -1), 1.0)));
	// ft_lstadd_back(&world, ft_lstnew(new_sphere(new_vector(0.8, -0.3, -1), 1.0)));
	// ft_lstadd_back(&world, ft_lstnew(new_sphere(new_vector(0.9, -0.3, -1), 1.0)));
	// ft_lstadd_back(&world, ft_lstnew(new_sphere(new_vector(1.0, -0.3, -1), 1.0)));
	// ft_lstadd_back(&world, ft_lstnew(new_sphere(new_vector(-0.1, -0.3, -1), 1.0)));
	// ft_lstadd_back(&world, ft_lstnew(new_sphere(new_vector(-0.2, -0.3, -1), 1.0)));
	// ft_lstadd_back(&world, ft_lstnew(new_sphere(new_vector(-0.3, -0.3, -1), 1.0)));
	// ft_lstadd_back(&world, ft_lstnew(new_sphere(new_vector(-0.4, -0.3, -1), 1.0)));
	// ft_lstadd_back(&world, ft_lstnew(new_sphere(new_vector(-0.5, -0.3, -1), 1.0)));
	// ft_lstadd_back(&world, ft_lstnew(new_sphere(new_vector(-0.6, -0.3, -1), 1.0)));
	// ft_lstadd_back(&world, ft_lstnew(new_sphere(new_vector(-0.7, -0.3, -1), 1.0)));
	// ft_lstadd_back(&world, ft_lstnew(new_sphere(new_vector(-0.8, -0.3, -1), 1.0)));
	// ft_lstadd_back(&world, ft_lstnew(new_sphere(new_vector(-0.9, -0.3, -1), 1.0)));
	// ft_lstadd_back(&world, ft_lstnew(new_sphere(new_vector(-1.0, -0.3, -1), 1.0)));


	// ft_lstadd_back(&world, ft_lstnew(new_sphere(new_vector(0, -0.4, -1), 1.0)));

	// ft_lstadd_back(&world, ft_lstnew(new_sphere(new_vector(0.1, -0.4, -1), 1.0)));
	// ft_lstadd_back(&world, ft_lstnew(new_sphere(new_vector(0.2, -0.4, -1), 1.0)));
	// ft_lstadd_back(&world, ft_lstnew(new_sphere(new_vector(0.3, -0.4, -1), 1.0)));
	// ft_lstadd_back(&world, ft_lstnew(new_sphere(new_vector(0.4, -0.4, -1), 1.0)));
	// ft_lstadd_back(&world, ft_lstnew(new_sphere(new_vector(0.5, -0.4, -1), 1.0)));
	// ft_lstadd_back(&world, ft_lstnew(new_sphere(new_vector(0.6, -0.4, -1), 1.0)));
	// ft_lstadd_back(&world, ft_lstnew(new_sphere(new_vector(0.7, -0.4, -1), 1.0)));
	// ft_lstadd_back(&world, ft_lstnew(new_sphere(new_vector(0.8, -0.4, -1), 1.0)));
	// ft_lstadd_back(&world, ft_lstnew(new_sphere(new_vector(0.9, -0.4, -1), 1.0)));
	// ft_lstadd_back(&world, ft_lstnew(new_sphere(new_vector(1.0, -0.4, -1), 1.0)));
	// ft_lstadd_back(&world, ft_lstnew(new_sphere(new_vector(-0.1, -0.4, -1), 1.0)));
	// ft_lstadd_back(&world, ft_lstnew(new_sphere(new_vector(-0.2, -0.4, -1), 1.0)));
	// ft_lstadd_back(&world, ft_lstnew(new_sphere(new_vector(-0.3, -0.4, -1), 1.0)));
	// ft_lstadd_back(&world, ft_lstnew(new_sphere(new_vector(-0.4, -0.4, -1), 1.0)));
	// ft_lstadd_back(&world, ft_lstnew(new_sphere(new_vector(-0.5, -0.4, -1), 1.0)));
	// ft_lstadd_back(&world, ft_lstnew(new_sphere(new_vector(-0.6, -0.4, -1), 1.0)));
	// ft_lstadd_back(&world, ft_lstnew(new_sphere(new_vector(-0.7, -0.4, -1), 1.0)));
	// ft_lstadd_back(&world, ft_lstnew(new_sphere(new_vector(-0.8, -0.4, -1), 1.0)));
	// ft_lstadd_back(&world, ft_lstnew(new_sphere(new_vector(-0.9, -0.4, -1), 1.0)));
	// ft_lstadd_back(&world, ft_lstnew(new_sphere(new_vector(-1.0, -0.4, -1), 1.0)));


	// ft_lstadd_back(&world, ft_lstnew(new_sphere(new_vector(0, -0.5, -1), 1.0)));

	// ft_lstadd_back(&world, ft_lstnew(new_sphere(new_vector(0.1, -0.5, -1), 1.0)));
	// ft_lstadd_back(&world, ft_lstnew(new_sphere(new_vector(0.2, -0.5, -1), 1.0)));
	// ft_lstadd_back(&world, ft_lstnew(new_sphere(new_vector(0.3, -0.5, -1), 1.0)));
	// ft_lstadd_back(&world, ft_lstnew(new_sphere(new_vector(0.4, -0.5, -1), 1.0)));
	// ft_lstadd_back(&world, ft_lstnew(new_sphere(new_vector(0.5, -0.5, -1), 1.0)));
	// ft_lstadd_back(&world, ft_lstnew(new_sphere(new_vector(0.6, -0.5, -1), 1.0)));
	// ft_lstadd_back(&world, ft_lstnew(new_sphere(new_vector(0.7, -0.5, -1), 1.0)));
	// ft_lstadd_back(&world, ft_lstnew(new_sphere(new_vector(0.8, -0.5, -1), 1.0)));
	// ft_lstadd_back(&world, ft_lstnew(new_sphere(new_vector(0.9, -0.5, -1), 1.0)));
	// ft_lstadd_back(&world, ft_lstnew(new_sphere(new_vector(1.0, -0.5, -1), 1.0)));
	// ft_lstadd_back(&world, ft_lstnew(new_sphere(new_vector(-0.1, -0.5, -1), 1.0)));
	// ft_lstadd_back(&world, ft_lstnew(new_sphere(new_vector(-0.2, -0.5, -1), 1.0)));
	// ft_lstadd_back(&world, ft_lstnew(new_sphere(new_vector(-0.3, -0.5, -1), 1.0)));
	// ft_lstadd_back(&world, ft_lstnew(new_sphere(new_vector(-0.4, -0.5, -1), 1.0)));
	// ft_lstadd_back(&world, ft_lstnew(new_sphere(new_vector(-0.5, -0.5, -1), 1.0)));
	// ft_lstadd_back(&world, ft_lstnew(new_sphere(new_vector(-0.6, -0.5, -1), 1.0)));
	// ft_lstadd_back(&world, ft_lstnew(new_sphere(new_vector(-0.7, -0.5, -1), 1.0)));
	// ft_lstadd_back(&world, ft_lstnew(new_sphere(new_vector(-0.8, -0.5, -1), 1.0)));
	// ft_lstadd_back(&world, ft_lstnew(new_sphere(new_vector(-0.9, -0.5, -1), 1.0)));
	// ft_lstadd_back(&world, ft_lstnew(new_sphere(new_vector(-1.0, -0.5, -1), 1.0)));