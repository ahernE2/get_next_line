/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alejhern <alejhern@student.42barcelona.co  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/16 20:21:14 by alejhern          #+#    #+#             */
/*   Updated: 2024/07/18 21:08:04 by alejhern         ###   ########.fr       */
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
	while (str[lenght] && str)
		lenght++;
	return (lenght);
}

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	unsigned char	*s;
	unsigned char	*d;
	size_t			index;

	s = (unsigned char *)src;
	d = (unsigned char *)dest;
	index = 0;
	while (index < n)
	{
		d[index] = s[index];
		index++;
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
	ft_memcpy(dup, str, size);
	dup[size] = '\0'; 
	return (dup);
}

void	*ft_realloc(void *ptr, size_t new_size)
{
	void	*new_ptr;

	if (!new_size)
	{
		free(ptr);
		return (NULL);
	}
	new_ptr = malloc(new_size);
	if (!new_ptr)
		return (NULL);
	if (!ptr)
		return (new_ptr);
	ft_memcpy(new_ptr, ptr, ft_strlen((char *)(unsigned char *)ptr));
	free(ptr);
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

char	*get_str_line(int fd, char *line, unsigned int iteration)
{
	if (buffer[1])
	{
		free(buffer[0]);
		buffer[0] = ft_strdup(buffer[1]);
	}
	buffer[0] = (char *)ft_realloc(buffer, ((ft_strlen(buffer[0]) + BUFFER_SIZE) * sizeof(char));
	if (!buffer)
		return (NULL);
	read(fd, buffer[0], BUFFER_SIZE);
	buffer[1] = ft_strchr(buffer[0], '\n');
	if (!buffer[1])
		get_str_line(fd, buffer);
	buffer[0] = (char *)ft_realloc(buffer[0], ft_strlen(buffer[0]));
	return (buffer);
}

char	*get_next_line(int fd)
{
	static char	**buffer;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	buffer = NULL;
	if (!buffer)
	{
		line = (char **)malloc(2 * sizeof(char *));
		if (!line)
			return (NULL);
	}
	get_str_line(fd, buffer);
	return (buffer[0]);
}

int	main(void)
{
	int		fd;
	char	*buffer;

	fd = open("test.txt", O_RDWR);
	if (fd == -1)
		return (1);
	buffer = get_next_line(fd);
	printf("%s\n", buffer);
	free(&buffer);
	close(fd);
	return (0);
}
