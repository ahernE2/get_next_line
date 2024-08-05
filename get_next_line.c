/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alejhern <alejhern@student.42barcelona.co  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/16 20:21:14 by alejhern          #+#    #+#             */
/*   Updated: 2024/08/05 23:19:41 by alejhern         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#ifndef BUFFER_SIZE
# define BUFFER_SIZE 1
#endif

size_t	ft_strlen(const char *str)
{
	size_t	lenght;

	lenght = 0;
	if (!str)
		return (lenght);
	while (str[lenght])
		lenght++;
	return (lenght);
}

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	unsigned char	*s;
	unsigned char	*d;

	s = (unsigned char *)src;
	d = (unsigned char *)dest;
	while (n--)
		*d++ = *s++;
	return (dest);
}

char	*ft_strdup(const char *str)
{
	size_t	size;
	char	*dup;

	if (!str)
		return (NULL);
	size = ft_strlen(str) + 1;
	dup = (char *)malloc(size * sizeof(char));
	if (!dup)
		return (NULL);
	ft_memcpy(dup, str, size);
	return (dup);
}

void	*ft_calloc(void ptr, size_t nmemb, size_t size)
{
	size_t			t_size;
	void			*arr;
	unsigned char	*arr_ptr;
	size_t			index;

	if (nmemb > 0 && size > 0 && nmemb > SIZE_MAX / size)
		return (NULL);
	t_size = nmemb * size;
	arr = malloc(t_size);
	if (!arr)
		return (NULL);
	arr_ptr = (unsigned char *)arr;
	index = 0;
	while (index < t_size)
	{
		*arr_ptr++ = '\0';
		index++;
	}
	return (arr);
}

void	*ft_realloc(void *ptr, size_t new_size)
{
	void	*new_ptr;
	size_t	size_old;
	size_t	size_cpy;

	if (!new_size)
	{
		free(ptr);
		return (NULL);
	}
	new_ptr = ft_calloc(new_size, sizeof(char));
	if (!new_ptr)
	{
		free(ptr);
		return (NULL);
	}
	if (ptr)
	{
		size_old = ft_strlen(ptr) + 1;
		if (size_old < new_size)
			size_cpy = size_old;
		else
			size_cpy = new_size;
		ft_memcpy(new_ptr, ptr, size_cpy);
		free(ptr);
	}
	return (new_ptr);
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

char	*ft_strjoin(char *s1, char *s2)
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
	t_size = s1_size + ft_strlen(s2) + 1;
	s1 = (char *)ft_realloc(s1, t_size * sizeof(char));
	if (!s1)
		return (NULL);
	while (*s2)
		s1[s1_size++] = *s2++;
	return (s1);
}

char	**buffer_check_nl(char **buffer, unsigned int buffer_ch)
{
	buffer[3] = ft_strchr(buffer[buffer_ch], '\n');
	if (buffer[3])
	{
		*buffer[3] = '\0';
		buffer[0] = ft_strjoin(buffer[0], buffer[buffer_ch]);
		buffer[0] = ft_strjoin(buffer[0], "\n");
		buffer[3] = ft_strdup(buffer[3] + 1);
		if (buffer[2])
			free(buffer[2]);
		buffer[2] = ft_strdup(buffer[3]);
		free(buffer[3]);
	}
	else
	{
		buffer[0] = ft_strjoin(buffer[0], buffer[buffer_ch]);
		free(buffer[2]);
		buffer[2] = NULL;
	}
	return (buffer);
}

char	**get_new_buffer(int fd, char **buffer)
{
	if (buffer[2])
	{
		buffer_check_nl(buffer, 2);
		if (buffer[2])
			return (buffer);
	}
	if (buffer[1])
		free(buffer[1]);
	buffer[1] = (char *)ft_calloc((BUFFER_SIZE + 1), sizeof(char));
	if (!buffer[1])
		return (NULL);
	while (1)
	{
		if (read(fd, buffer[1], BUFFER_SIZE) <= 0)
		{
			free(buffer[0]);
			buffer[0] = NULL;
			break ;
		}
		buffer_check_nl(buffer, 1);
		if (buffer[2])
			break ;
	}
	return (buffer);
}

char	*get_next_line(int fd)
{
	static char	*buffer[4];

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	if (buffer[0])
	{
		free(buffer[0]);
		buffer[0] = NULL;
	}
	get_new_buffer(fd, buffer);
	free(buffer[1]);
	buffer[1] = NULL;
	return (buffer[0]);
}

int	main(void)
{
	int		fd;
	char	*line;

	fd = open("test.txt", O_RDWR);
	if (fd == -1)
		return (1);
	while ((line = get_next_line(fd)) != NULL)
		printf("%s", line);
	free(line);
	close(fd);
	return (0);
}
