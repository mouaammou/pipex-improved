/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   help_split.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mouaammo <mouaammo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/20 16:18:43 by mouaammo          #+#    #+#             */
/*   Updated: 2022/12/20 20:02:21 by mouaammo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "./libft/libft.h"
#include "pipex.h"

char	**free_split(char **tab)
{
	unsigned int	i;

	i = 0;
	while (tab[i])
		free(tab[i++]);
	free(tab);
	return (NULL);
}

int	ft_norm1(char *s, int *i, int *flag)
{
	int	word_len;

	word_len = 0;
	(*flag) = 1;
	while (s[(*i)] && (s[(*i)] == '\'' || s[(*i)] == '"'))
		(*i)++;
	while (s[(*i)] && (s[(*i)] != '\'' && s[(*i)] != '"'))
	{
		word_len++;
		(*i)++;
	}
	return (word_len);
}

int	ft_norm2(char *s, int *i, char c)
{
	int		word_len;

	word_len = 0;
	while (s[(*i)] && s[(*i)] != c && s[(*i)] != '\'' && s[(*i)] != '"')
	{
		word_len++;
		(*i)++;
	}
	return (word_len);
}

int	wck(char *s, int *flag, char c, int *i)
{
	int		len;

	len = 0;
	if (s[*i] != '\0' && *flag == 0 && (s[*i] == '\'' || s[*i] == '"'))
	{
		len = ft_norm1(s, i, flag);
	}
	if (s[*i] != '\0' && s[*i] != c && s[*i] != '\'' && s[*i] != '"')
	{
		len = ft_norm2(s, i, c);
	}
	*flag = 0;
	return (len);
}

char	**split_improved(char *s, char c, char **split)
{
	int		flag;
	int		len;
	int		i;
	int		j;

	len = 0;
	i = 0;
	j = 0;
	flag = 0;
	while (s && s[i] != '\0')
	{
		len = wck(s, &flag, c, &i);
		if (len)
		{
			split[j] = ft_substr(s, i - len, len);
			if (!split[j])
				return (free_split(split));
			j++;
		}
		if (s[i] != '\0')
			i++;
	}
	return (split);
}
