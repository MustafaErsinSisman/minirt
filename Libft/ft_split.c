/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yozlu <yozlu@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/23 19:06:20 by musisman          #+#    #+#             */
/*   Updated: 2026/01/03 17:20:42 by yozlu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	check_consecutive(char const *s, char c)
{
	size_t	i;

	i = 0;
	if (c != ',')
		return (0);
	while (s[i])
	{
		if (s[i] == c && s[i + 1] == c)
			return (1);
		i++;
	}
	return (0);
}

static size_t	world_count(char const *s, char c)
{
	size_t	wc;
	size_t	i;

	i = 0;
	wc = 0;
	while (s[i])
	{
		if (s[i] == c)
			i++;
		else
		{
			while (s[i] && s[i] != c)
				i++;
			wc++;
		}
	}
	return (wc);
}

static size_t	control(char const *s, size_t start, size_t i)
{
	if (s[start + i])
		return (1);
	return (0);
}

static char	**last_sp(char **sp, char const *s, char c)
{
	size_t	start;
	size_t	i;
	size_t	wc;

	i = 0;
	start = 0;
	wc = 0;
	while (s[start])
	{
		i = 0;
		while (s[start + i] && s[start + i] != c)
			i++;
		if (i > 0)
		{
			sp[wc] = ft_substr(s, start, i);
			if (!sp[wc])
				return (NULL);
			wc++;
		}
		start += i + control(s, start, i);
	}
	return (sp);
}

char	**ft_split(char const *s, char c)
{
	char	**sp;
	size_t	wc;

	if (check_consecutive(s, c))
		return (NULL);
	wc = world_count(s, c);
	sp = ft_calloc(wc + 1, sizeof(char *));
	if (!sp)
		return (NULL);
	if (!last_sp(sp, s, c))
		return (NULL);
	return (sp);
}
