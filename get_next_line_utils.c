/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alejhern <alejhern@student.42barcelona.co  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/06 13:55:28 by alejhern          #+#    #+#             */
/*   Updated: 2024/09/17 09:53:07 by alejhern         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

size_t	ft_strlen(const char *str)
{
	size_t	lenght;

	lenght = 0;
	while (str[lenght])
		lenght++;
	return (lenght);
}

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	unsigned char	*d;
	unsigned char	*s;
	size_t			i;

	d = (unsigned char *) dest;
	s = (unsigned char *) src;
	if (s < d && s + n > d)
	{
		i = n;
		while (i > 0)
		{
			d[i - 1] = s[i -1];
			i--;
		}
	}
	else
	{
		i = 0;
		while (i < n)
		{
			d[i] = s[i];
			i++;
		}
	}
	return (dest);
}

char	*ft_strdup(const char *str)
{
	size_t	size;
	char	*dup;

	size = ft_strlen(str) + 1;
	dup = (char *)malloc(size * sizeof(char));
	if (!dup)
		return (NULL);
	ft_memmove(dup, str, size);
	return (dup);
}

char	*ft_strchr(const char *str, int c)
{
	while (*str)
	{
		if (*str == (char)c)
			return ((char *)str);
		str++;
	}
	if (*str == (char)c)
		return ((char *)str);
	return (NULL);
}

char	*ft_strjoin(char *s1, char *s2, int put_nl)
{
	size_t	t_size;
	size_t	s1_size;

	if (!s1 && !s2)
		return (NULL);
	if (!s1)
		return (ft_strdup(s2));
	if (!s2)
		return (s1);
	s1_size = ft_strlen(s1);
	t_size = s1_size + ft_strlen(s2) + 1 + put_nl;
	s1 = (char *)ft_realloc(s1, t_size * sizeof(char));
	if (!s1)
		return (NULL);
	while (*s2)
		s1[s1_size++] = *s2++;
	if (put_nl)
		s1[s1_size++] = '\n';
	return (s1);
}
