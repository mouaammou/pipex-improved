/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mouaammo <mouaammo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/15 18:24:21 by mouaammo          #+#    #+#             */
/*   Updated: 2022/12/20 20:27:54 by mouaammo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

char	*free_all(char **ptr)
{
	int	i;

	i = 0;
	if (!ptr)
		return (NULL);
	while (ptr[i])
		free(ptr[i++]);
	free(ptr);
	return (NULL);
}

char	*check_path(char **paths, char *arv)
{
	char	*full_path;
	int		i;
	char	*initial_path;

	i = -1;
	if (!paths || !arv)
		return (NULL);
	if (ft_strnstr(arv, "./", 2))
		return (ft_strdup(arv + 2));
	if ((access(arv, F_OK) == 0 && ft_strchr(arv, '/'))
		|| (access(arv, F_OK) == 0 && !ft_strchr(arv, '/')))
		return (ft_strdup(arv));
	else if (access(arv, F_OK) == -1 && ft_strchr(arv, '/'))
		return (NULL);
	while (paths[++i])
	{
		initial_path = paths[i];
		paths[i] = ft_strjoin(initial_path, "/");
		free(initial_path);
		full_path = ft_strjoin(paths[i], arv);
		if (access(full_path, F_OK) == 0)
			return (full_path);
		free(full_path);
	}
	return (NULL);
}

char	*get_path(char **ev)
{
	if (!ev)
		return (NULL);
	while (*ev)
	{
		if (ft_strncmp("PATH=", *ev, 5) == 0)
			return (*ev + 5);
		ev++;
	}
	return (NULL);
}

void	error(void)
{
	perror("\033[31mError\033[0m");
	exit(EXIT_FAILURE);
}

void	execute(char **env, char *av, int *fd)
{
	char	**args;
	char	*file;
	char	**paths;
	int		i;

	i = -1;
	if (!av || !env || !fd)
		error();
	close(fd[0]);
	close(fd[1]);
	args = ft_split_proc(av, ' ');
	paths = ft_split_proc(get_path(env), ':');
	file = check_path(paths, args[0]);
	free_all(paths);
	if (execve(file, args, NULL))
	{
		if (file)
			free(file);
		free_all(args);
		error();
	}
}
