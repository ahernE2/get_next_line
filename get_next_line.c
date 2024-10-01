/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alejhern <alejhern@student.42barcelona.co  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/16 20:21:14 by alejhern          #+#    #+#             */
/*   Updated: 2024/08/09 11:12:45 by alejhern         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

void	*ft_calloc(size_t nmemb, size_t size)
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

	if (!new_size)
	{
		free(ptr);
		return (NULL);
	}
	new_ptr = ft_calloc(new_size, sizeof(char));
	if (ptr && new_ptr)
	{
		if (ft_strlen(ptr) + 1 < new_size)
			ft_memmove(new_ptr, ptr, ft_strlen(ptr) + 1);
		else
			ft_memmove(new_ptr, ptr, new_size);
	}
	free(ptr);
	return (new_ptr);
}

static char	**buffer_check_nl(char **buffer)
{
	buffer[2] = ft_strchr(buffer[1], '\n');
	if (buffer[2])
	{
		*buffer[2] = '\0';
		buffer[0] = ft_strjoin(buffer[0], buffer[1], 1);
		ft_memmove(buffer[1], buffer[2] + 1, ft_strlen(buffer[2] + 1) + 1);
	}
	else
	{
		buffer[0] = ft_strjoin(buffer[0], buffer[1], 0);
		*buffer[1] = '\0';
	}
	return (buffer);
}

static char	**get_new_buffer(int fd, char **buffer)
{
	int	bytes_read;

	buffer_check_nl(buffer);
	if (buffer[2] || !buffer[0])
		return (buffer);
	while (!buffer[2])
	{
		bytes_read = read(fd, buffer[1], BUFFER_SIZE);
		if (bytes_read < 0)
		{
			free(buffer[0]);
			buffer[0] = NULL;
			break ;
		}
		buffer[1][bytes_read] = '\0';
		if (bytes_read == 0)
			break ;
		buffer_check_nl(buffer);
	}
	return (buffer);
}

char	*get_next_line(int fd)
{
	static char	*buffer[1024][4] = {{NULL}};

	if (fd < 0 || fd > 1024 || BUFFER_SIZE <= 0)
		return (NULL);
	if (!buffer[fd][1])
	{
		buffer[fd][1] = (char *)ft_calloc((BUFFER_SIZE + 1), sizeof(char));
		if (!buffer[fd][1])
			return (NULL);
	}
	buffer[fd][0] = ft_strdup("");
	get_new_buffer(fd, buffer[fd]);
	if (buffer[fd][0] && buffer[fd][0][0] == '\0')
	{
		free(buffer[fd][0]);
		buffer[fd][0] = NULL;
	}
	if (!buffer[fd][0])
	{
		free(buffer[fd][1]);
		buffer[fd][1] = NULL;
	}
	return (buffer[fd][0]);
}
