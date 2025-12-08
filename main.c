/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yozlu <yozlu@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/03 16:31:32 by yozlu             #+#    #+#             */
/*   Updated: 2025/12/08 19:39:30 by yozlu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int	map_height(char *file)
{
	char	*line;
	int		fd;
	int		i;
	
	fd = open(file, O_RDONLY);
	if (fd < 0)
	{
		//hata durumu gelecek
	}
	i = 0;
	line = get_next_line(fd);
	if (!line)
	{
		//hata durumu gelecek
	}
	while (line)
	{
		i++;
		line = get_next_line(fd);
	}
	close(fd);
	return (i);
}

char	**read_map(char *file)
{
	int		i;
	int		fd;
    int     line_count;
	char	*line;
	char	**values;

	line_count = map_height(file);/// VERİLEN DOSYAYI OKUYUP SONRASINDA KONTROLE GÖNDERECEĞİM
	values = ft_malloc((line_count + 1) * sizeof(char *));
	if (!values)
		return (0);
	fd = open(file, O_RDONLY);
	if (fd < 0)
	{
		//hata durumu gelecek
	}
	i = 0;
	line = get_next_line(fd);
	while (line != NULL)
	{
		if (line[ft_strlen(line) - 1] == '\n')
			line[ft_strlen(line) - 1] = '\0';
		values[i++] = line;
		line = get_next_line(fd);
	}
	values[i] = NULL;
	close(fd);
	return (values);
}

t_list	*world_objects(t_obje_list *pre_objects)  // TODO parserdan gelecek t_objects_list structu olacak
{
	t_list	*world;
	t_obje_list *temp;

	temp = pre_objects;
	while (temp)
	{
		if (temp->type == SPHERE)
			ft_lstadd_back(&world, ft_lstnew(new_sphere(temp->objects.sphere.pos, temp->objects.sphere.radius, temp->objects.sphere.rgb)));
		else if (temp->type == PLANE)
			ft_lstadd_back(&world, ft_lstnew(new_plane(temp->objects.plane.pos, temp->objects.plane.normal, temp->objects.plane.rgb)));
		else if (temp->type == CYLINDER)
			ft_lstadd_back(&world, ft_lstnew(new_cylinder(temp->objects.cylinder.pos, temp->objects.cylinder.normal, (double[2]){temp->objects.cylinder.diameter, temp->objects.cylinder.height}, temp->objects.cylinder.rgb)));
		temp = temp->next;
	}
	return (world);
}

t_data *prepare_datas(t_obje_list *pre_objects)
{
	t_data *datas;

	datas = ft_malloc(sizeof(t_data));
	datas->world = world_objects(pre_objects);
	while (pre_objects)
	{
		if (pre_objects->type == AMBIANT)
		{
			datas->ambient.range = pre_objects->objects.ambiant.range;
			datas->ambient.rgb = pre_objects->objects.ambiant.rgb;
		}
		else if (pre_objects->type == CAMERA)
		{
			datas->camera.fov = pre_objects->objects.camera.fov;
			datas->camera.normal = pre_objects->objects.camera.normal;
			datas->camera.pos = pre_objects->objects.camera.pos;
		}
		else if (pre_objects->type == LIGHT)
		{
			datas->light.pos = pre_objects->objects.light.pos;
			datas->light.range = pre_objects->objects.light.range;
			datas->light.rgb = pre_objects->objects.light.rgb;
		}
		pre_objects = pre_objects->next;
	}
	return (datas);
}

static bool	mlx_process(t_data *data)
{
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
	camera_render(data, &vars);
	mlx_put_image_to_window(vars.mlx, vars.win, vars.img, 0, 0); // * image windowa çizildi
	mlx_key_hook(vars.win, key_hook, &vars); // * key hook eklendi bu fonksiyon pencere açıkken klavye girişlerini dinler ve belirli bir tuşa basıldığında belirli bir fonksiyonu çağırır
	mlx_hook(vars.win, 17, 0, exit_func, &vars); // * pencere kapatma butonuna tıklanınca exit_func fonksiyonu çağrılır
	mlx_loop(vars.mlx); // * mlx döngüsü başlatıldı bu fonksiyon, pencere açık olduğu sürece sürekli olarak çalışır ve olayları dinler
	return (true);
}



int	main(int argc, char **argv)
{
	char **values;
	t_obje_list *pre_objects;
	
	pre_objects = NULL;
    if (argc == 1)
		exit(EXIT_SUCCESS);
	file_extension(argv[1]);
	values = read_map(argv[1]);
	if(chr_control(values))
	{
		//hata durumu
	}
	// int i = 0;
	// while (values[i])
	// 	printf("%s\n", values[i++]);
	controller(values, pre_objects);
	if (!mlx_process(prepare_datas(pre_objects)))
		return (ft_free(), 1);
	ft_free();
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
