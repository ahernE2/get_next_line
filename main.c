/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alejhern <alejhern@student.42barcelona.co  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/08 12:39:23 by alejhern          #+#    #+#             */
/*   Updated: 2024/08/08 20:53:27 by alejhern         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

void	close_fds(int *fds, int count_files)
{
	int	i;

	i = 0;
	while (i < count_files)
	{
		close(fds[i]);
		i++;
	}
}

void	print_get_next_line(int count_files, int *fds)
{
	int		index;
	int		still_reading;
	char	*line;

	still_reading = 1;
	while (still_reading)
	{
		still_reading = 0;
		index = 0;
		while (index < count_files)
		{
			line = get_next_line(fds[index]);
			if (line)
			{
				printf("%s", line);
				free(line);
				line = NULL;
				still_reading = 1;
			}
			index++;
		}
	}
}

int	main(int argc, char **argv)
{
	char	**files;
	int		*fds;
	int		i;

	if (argc < 2)
		return (0);
	files = (char **)malloc((argc - 1) * sizeof(char *));
	if (!files)
		return (1);
	i = 0;
	while (i < (argc - 1))
	{
		files[i] = argv[i + 1];
		i++;
	}
	files[i] = NULL;
	fds = (int *)malloc(sizeof(int) * (argc - 1));
	if (!fds)
	{
		free(files);
		return (1);
	}
	i = 0;
	while (i < (argc - 1))
	{
		fds[i] = open(files[i], O_RDONLY);
		i++;
	}
	print_get_next_line((argc - 1), fds);
	close_fds(fds, (argc - 1));
	free(fds);
	free(files);
	return (0);
}
