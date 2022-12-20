/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mouaammo <mouaammo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/15 18:55:28 by mouaammo          #+#    #+#             */
/*   Updated: 2022/12/20 20:24:44 by mouaammo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	usage(void)
{
	ft_putstr_fd("Bad arguments\n", 1);
	ft_putstr_fd("usage: ./pipex file1 cmd1 cmd2 cmd3 ... cmdn file2\n", 1);
	exit(EXIT_FAILURE);
}

void	here_doc(int ac, char *limiter)
{
	int		pid;
	char	*line;
	int		fd[2];

	if (ac < 6)
		usage();
	if (pipe(fd) == -1)
		error();
	pid = fork();
	if (pid == -1)
		error();
	if (pid == 0)
	{
		close(fd[0]);
		read_from_input(fd, limiter, &line);
	}
	dup2(fd[0], 0);
	close(fd[1]);
	wait(NULL);
}

void	process(int i, char **av, char **env, int *fd)
{
	int	pid;

	if (pipe(fd) == -1)
		error();
	pid = fork();
	if (pid == -1)
		error();
	if (pid == 0)
	{
		dup2(fd[1], 1);
		execute(env, av[i], fd);
	}
	dup2(fd[0], 0);
	close(fd[1]);
	wait(NULL);
}

void	check_here_doc(int *i, int *out_fd, int ac, char **av)
{
	int	in_fd;

	if (ft_strcmp(av[1], "here_doc") == 0)
	{
		*i = 3;
		here_doc(ac, av[2]);
		*out_fd = open_file(av[ac - 1], "here_doc");
	}
	else
	{
		*i = 2;
		in_fd = open(av[1], O_RDWR, 0777);
		dup2(in_fd, 0);
		*out_fd = open_file(av[ac - 1], "outfile");
		if (in_fd == -1)
		{
			perror("");
			*i = 3;
			dup2(*out_fd, 0);
		}
		close(in_fd);
	}
}

int	main(int ac, char **av, char **env)
{
	int	i;
	int	fd[2];
	int	out_fd;

	if (ac >= 5)
	{
		check_here_doc(&i, &out_fd, ac, av);
		while (i < ac - 2)
			process(i++, av, env, fd);
		dup2(out_fd, 1);
		close(out_fd);
		execute(env, av[ac - 2], fd);
	}
	else
		usage();
	return (0);
}
