/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mouaammo <mouaammo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/14 17:49:54 by mouaammo          #+#    #+#             */
/*   Updated: 2022/12/20 20:08:48 by mouaammo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	ft_strcmp(const char *s1, const char *s2)
{
	if (!s1 || !s2)
		return (0);
	while (*s1 == *s2 && *s1 && *s2)
	{
		s1++;
		s2++;
	}
	return (*s1 - *s2);
}

void	read_from_input(int *fd, char *limiter, char **line)
{
	while (1)
	{
		*line = get_next_line(0);
		if (ft_strncmp(*line, limiter, ft_strlen(*line) - 1) == 0)
			exit(EXIT_SUCCESS);
		write(fd[1], *line, ft_strlen(*line));
	}
}

int	open_file(char *file, char *type)
{
	int		fd;

	fd = -1;
	if (ft_strncmp(type, "in", 2) == 0)
		fd = open(file, O_RDWR, 0777);
	else if (ft_strncmp(type, "out", 3) == 0)
		fd = open(file, O_RDWR | O_CREAT | O_TRUNC, 0777);
	else if (ft_strncmp(type, "here_doc", 8) == 0)
		fd = open (file, O_RDWR | O_CREAT | O_APPEND, 0777);
	if (fd == -1)
		error();
	return (fd);
}
