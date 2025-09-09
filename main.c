/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yozlu <yozlu@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/03 16:31:32 by yozlu             #+#    #+#             */
/*   Updated: 2025/09/09 19:26:38 by yozlu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minirt.h>

int	map_height(char *file)
{
	char	*line;
	int		fd;
	int		i;
	
	fd = open(file, O_RDONLY);
	if (fd < 0)
		return (free_game(game), error_message(4), 0);
	i = 0;
	line = get_next_line(fd);
	if (!line)
		return (free_game(game), error_message(0), 0);
	while (line)
	{
		i++;
		free(line);
		line = get_next_line(fd);
	}
	close(fd);
	return (i);
}

int	read_map(char *file)
{
	int		i;
	int		fd;
    int     line_count;
	char	*line;
	char	**map;

	line_count = map_height(file);/// VERİLEN DOSYAYI OKUYUP SONRASINDA KONTROLE GÖNDERECEĞİM
	map = malloc(line_count * sizeof(char *) + 1);
	if (!map)
		return (0);
	fd = open(file, O_RDONLY);
	if (fd < 0)
		return (free_game(game), error_message(4), 0);
	i = 0;
	line = get_next_line(fd);
	while (line != NULL)
	{
		if (line[ft_strlen(line) - 1] == '\n')
			line[ft_strlen(line) - 1] = '\0';
		map[i++] = line;
		line = get_next_line(fd);
	}
	close(fd);
	game->map = map;
	game->width = ft_strlen(map[0]);
	return (1);
}

int main(int argc, char **argv)
{
    if (argc == 1)
		exit(EXIT_SUCCESS);
    file_extension(argv[1]);
    return 0;
}
