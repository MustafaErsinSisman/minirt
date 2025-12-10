/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: musisman <musisman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/03 16:31:32 by yozlu             #+#    #+#             */
/*   Updated: 2025/12/10 18:58:03 by musisman         ###   ########.fr       */
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
		error_message("Failed to open the file\n");
	i = 0;
	line = get_next_line(fd);
	if (!line)
		error_message("File is empty\n");
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
	int		line_count;
	char	*line;
	char	**values;

	line_count = map_height(file);
	values = ft_malloc((line_count + 1) * sizeof(char *));
	if (!values)
		return (0);
	fd = open(file, O_RDONLY);
	if (fd < 0)
		error_message("Failed to open the file\n");
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

t_list	*world_objects(t_obje_list *pre_objects)
{
	t_list		*world;
	t_obje_list	*temp;

	world = NULL;
	temp = pre_objects;
	while (temp)
	{
		if (temp->type == SPHERE)
			ft_lstadd_back(&world, ft_lstnew(new_sphere
					(temp->objects.sphere.pos, temp->objects.sphere.radius,
						temp->objects.sphere.rgb)));
		else if (temp->type == PLANE)
			ft_lstadd_back(&world, ft_lstnew(new_plane
					(temp->objects.plane.pos, temp->objects.plane.normal,
						temp->objects.plane.rgb)));
		else if (temp->type == CYLINDER)
			ft_lstadd_back(&world, ft_lstnew(new_cylinder
					(temp->objects.cylinder.pos, temp->objects.cylinder.normal,
						(double [2]){temp->objects.cylinder.diameter,
						temp->objects.cylinder.height},
						temp->objects.cylinder.rgb)));
		temp = temp->next;
	}
	return (world);
}

t_data	*prepare_datas(t_obje_list *pre_objects, t_data *datas)
{
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

int	main(int argc, char **argv)
{
	char		**values;
	t_obje_list	*pre_objects;
	t_data		*datas;

	datas = NULL;
	pre_objects = NULL;
	if (argc == 1)
		exit(EXIT_SUCCESS);
	file_extension(argv[1]);
	values = read_map(argv[1]);
	chr_control(values);
	controller(values, &pre_objects, NULL, NULL);
	if (!mlx_process(prepare_datas(pre_objects, datas)))
		return (ft_free(), 1);
	ft_free();
	return (0);
}
