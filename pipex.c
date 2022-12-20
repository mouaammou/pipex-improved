/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mouaammo <mouaammo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/14 17:49:44 by mouaammo          #+#    #+#             */
/*   Updated: 2022/12/20 18:47:00 by mouaammo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	usage(void)
{
	ft_putstr_fd("\n\033[31mBab arguments\033[0m\n", 1);
	ft_putstr_fd("Usage: ./pipex infile <cmd1> <cmd2> outfile\n\n", 1);
	exit(EXIT_FAILURE);
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

void	pipex(int ac, char **av, char **env)
{
	int	i;
	int	fd[2];
	int	out_fd;
	int	in_file;

	i = 2;
	in_file = open(av[1], O_RDONLY, 0777);
	out_fd = open(av[ac - 1], O_RDWR | O_CREAT | O_TRUNC, 0777);
	if (out_fd == -1)
		error();
	dup2(in_file, 0);
	close(in_file);
	if (in_file == -1)
	{
		perror("");
		i = ac -2;
		dup2(out_fd, 0);
	}
	while (i < ac - 2)
		process(i++, av, env, fd);
	dup2(out_fd, 1);
	close(out_fd);
	execute(env, av[ac - 2], fd);
}

int	main(int ac, char **av, char **env)
{
	if (ac == 5)
		pipex(ac, av, env);
	else
		usage();
	return (0);
}
