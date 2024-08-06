/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alejhern <alejhern@student.42barcelona.co  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/06 14:18:57 by alejhern          #+#    #+#             */
/*   Updated: 2024/08/06 14:19:02 by alejhern         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 1
# endif

# include <fcntl.h>
# include <stdint.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>

// Declarations from get_next_line_utils.c
void	*ft_memcpy(void *dest, const void *src, size_t n);
char	*ft_strdup(const char *str);
char	*ft_strchr(const char *str, int c);
char	*ft_strjoin(char *s1, char *s2);
size_t	ft_strlen(const char *str);
// Declarations from get_next_line.c
void	*ft_calloc(size_t nmemb, size_t size);
void	*ft_realloc(void *ptr, size_t new_size);
char	*get_next_line(int fd);
#endif