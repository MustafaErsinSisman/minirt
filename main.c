/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yozlu <yozlu@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/03 16:31:32 by yozlu             #+#    #+#             */
/*   Updated: 2025/10/02 16:49:51 by yozlu            ###   ########.fr       */
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
		free(line);
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
	values = malloc(line_count * sizeof(char *) + 1);
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
	close(fd);
	return (values);
}

int main(int argc, char **argv)
{
	char **values;
	
    if (argc == 1)
		exit(EXIT_SUCCESS);
    file_extension(argv[1]);
	values = read_map(argv[1]);
	if(chr_control(values))
	{
		//hata durumu
	}
	controller(values);
	int i = 0;
	while (values[i])
		printf("%s\n", values[i++]);
    return 0;
}
