/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alejhern <alejhern@student.42barcelona.co  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/16 20:21:14 by alejhern          #+#    #+#             */
/*   Updated: 2024/08/03 16:49:47 by alejhern         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>
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
	dup[size] = '\0';
	return (dup);
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
	new_ptr = malloc(new_size);
	if (!new_ptr)
		return (NULL);
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

char    *ft_strjoin(char *s1, char *s2)
{
        size_t  t_size;
	size_t	index;
        char    *arr;

        if (!s1 && !s2)
                return (NULL);
        if (!s1)
                return (ft_strdup(s2));
        if (!s2)
                return (ft_strdup(s1));
        t_size = ft_strlen(s1) + ft_strlen(s2) + 1;
        arr = (char *)malloc(t_size * sizeof(char));
        if (!arr)
                return (NULL);
	index = 0;
        while (*s1)
		arr[index++] = *s1++;
	while (*s2)
		arr[index++] = *s2++;
	arr[index] = '\0';
        return (arr);
}

char	**buffer_check_nl(char **buffer, unsigned int buffer_ch)
{
	buffer[2] = ft_strchr(buffer[buffer_ch], '\n');
	if (buffer[2])
	{
		*(buffer[2] + 1) = '\0';
		buffer[2] = NULL;
		buffer[2] = ft_strdup(buffer[buffer_ch] + ft_strlen(buffer[buffer_ch]) + 1);
	}
	return (buffer);
}

char	**get_new_buffer(int fd, char **buffer)
{
	size_t	bytes_read;

	if (buffer[2])
	{
		buffer[0] = ft_strjoin(buffer[0], buffer[2]);
		buffer_check_nl(buffer, 0);
		if (buffer[2])
			return (buffer);
	}
	buffer[1] = (char *)malloc((BUFFER_SIZE + 1) * sizeof(char));
	if (!buffer[1])
		return (NULL);
	bytes_read = read(fd, buffer[1], BUFFER_SIZE);
	if (bytes_read > 0)
	{
        	buffer[1][bytes_read] = '\0';
			buffer_check_nl(buffer, 1);
			buffer[0] = ft_strjoin(buffer[0], buffer[1]);
			if (!buffer[2])
				get_new_buffer(fd, buffer);
	}
	return (buffer);
}

char	*get_next_line(int fd)
{
	static char	*buffer[3];

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
	// line = get_next_line(fd);
	// printf("%s", line);
	while ((line = get_next_line(fd)) != NULL)
        	printf("%s", line);
	free(line);
	close(fd);
	return (0);
}
