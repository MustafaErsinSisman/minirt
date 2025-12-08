/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yozlu <yozlu@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/09 19:01:48 by yozlu             #+#    #+#             */
/*   Updated: 2025/10/24 16:28:50 by yozlu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static char	*ft_strchr_1(const char *s, int c)
{
	char	a;

	a = (char)c;
	if (!s)
		return (NULL);
	while (*s)
	{
		if (*s == (unsigned char)a)
			return ((char *)s);
		s++;
	}
	if (a == '\0')
		return ((char *)s);
	return (0);
}

char	*ft_line_before(char *station)
{
	char	*result;
	int		i;

	i = 0;
	if (!station[i])
		return (NULL);
	while (station[i] && station[i] != '\n')
		i++;
	result = ft_substr_1(station, 0, i + (station[i] == '\n'));
	if (!result)
		return (NULL);
	if (station[i] == '\n')
	{
		result[i] = station[i];
		i++;
	}
	result[i] = '\0';
	return (result);
}

char	*ft_line_after(char *station)
{
	char	*after_station;
	char	*temp;

	if (!station[0])
		return (NULL);
	temp = ft_strchr_1(station, '\n');
	if (temp)
	{
		after_station = ft_substr_1(temp, 1, ft_strlen_1(temp));
		if (!after_station)
			return (NULL);
		return (after_station);
	}
	temp = ft_strchr_1(station, '\0');
	after_station = ft_substr_1(temp, 0, ft_strlen_1(temp));
	if (!after_station)
		return (NULL);
	return (after_station);
}

char	*station_read(char *buffer, char *station, int fd)
{
	int	count;

	count = 1;
	while (!ft_strchr_1(station, '\n') && count != 0)
	{
		count = read(fd, buffer, BUFFER_SIZE);
		if (count == -1)
		{
			if (station)
				station = NULL;
			return (NULL);
		}
		buffer[count] = '\0';
		station = ft_strjoin_1(station, buffer);
	}
	return (station);
}

char	*get_next_line(int fd)
{
	static char	*station;
	char		*result;
	char		*buffer;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	buffer = ft_malloc((BUFFER_SIZE + 1));
	if (buffer == NULL)
		return (NULL);
	station = station_read(buffer, station, fd);
	if (!station)
		return (NULL);
	result = ft_line_before(station);
	station = ft_line_after(station);
	return (result);
}
