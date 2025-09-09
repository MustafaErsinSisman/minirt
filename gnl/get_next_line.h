/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yozlu <yozlu@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/09 19:01:56 by yozlu             #+#    #+#             */
/*   Updated: 2025/09/09 19:01:58 by yozlu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <fcntl.h>
# include <stdlib.h>
# include <unistd.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 1000000
# endif

char	*get_next_line(int fd);
char	*ft_line_before(char *station);
char	*ft_line_after(char *station);
char	*ft_strjoin_1(char *s1, char const *s2);
size_t	ft_strlen_1(const char *s);
char	*ft_substr_1(char *s, unsigned int start, size_t len);
char	*station_read(char *buffer, char *station, int fd);

#endif