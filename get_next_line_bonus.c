/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alejhern <alejhern@student.42barcelona.co  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/07 19:06:49 by alejhern          #+#    #+#             */
/*   Updated: 2024/08/08 23:30:43 by alejhern         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

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
			ft_memcpy(new_ptr, ptr, ft_strlen(ptr) + 1);
		else
			ft_memcpy(new_ptr, ptr, new_size);
	}
	free(ptr);
	return (new_ptr);
}

static char	**buffer_check_nl(char **buffer, unsigned int buffer_ch)
{
	buffer[3] = ft_strchr(buffer[buffer_ch], '\n');
	if (buffer[3])
	{
		*buffer[3] = '\0';
		buffer[0] = ft_strjoin(buffer[0], buffer[buffer_ch]);
		buffer[0] = ft_strjoin(buffer[0], "\n");
		buffer[3] = ft_strdup(buffer[3] + 1);
		free(buffer[2]);
		buffer[2] = ft_strdup(buffer[3]);
		free(buffer[3]);
		buffer[3] = NULL;
	}
	else
	{
		buffer[0] = ft_strjoin(buffer[0], buffer[buffer_ch]);
		free(buffer[2]);
		buffer[2] = NULL;
	}
	return (buffer);
}

static char	**get_new_buffer(int fd, char **buffer)
{
	int	bytes_read;

	if (buffer[2])
	{
		buffer_check_nl(buffer, 2);
		if (buffer[2])
			return (buffer);
	}
	while (1)
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
		buffer_check_nl(buffer, 1);
		if (buffer[2])
			break ;
	}
	return (buffer);
}

char	*get_next_line(int fd)
{
	static char	*buffer[1024][4];

	if (fd < 0 || fd > 1024 || BUFFER_SIZE <= 0)
		return (NULL);
	buffer[fd][1] = (char *)ft_calloc((BUFFER_SIZE + 1), sizeof(char));
	if (!buffer[fd][1])
		return (NULL);
	buffer[fd][0] = NULL;
	get_new_buffer(fd, buffer[fd]);
	if (buffer[fd][0] && buffer[fd][0][0] == '\0')
	{
		free(buffer[fd][0]);
		buffer[fd][0] = NULL;
	}
	if (!buffer[fd][0])
	{
		free(buffer[fd][2]);
		buffer[fd][2] = NULL;
	}
	free(buffer[fd][1]);
	return (buffer[fd][0]);
}
