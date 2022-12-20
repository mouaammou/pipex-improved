/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   count_words.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mouaammo <mouaammo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/20 18:11:40 by mouaammo          #+#    #+#             */
/*   Updated: 2022/12/20 18:12:14 by mouaammo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>

void	quotes_func(char *s, int *i, int *size, int *flag)
{
	(*size)++;
	(*flag) = 1;
	while (s[(*i)] && (s[(*i)] == '\'' || s[(*i)] == '"'))
		(*i)++;
	while (s[(*i)] && (s[(*i)] != '\'' && s[(*i)] != '"'))
		(*i)++;
}

void	scape(char *s, int *i, int *size, char c)
{
	(*size)++;
	while (s[(*i)] && s[(*i)] != c && s[(*i)] != '\'' && s[(*i)] != '"')
		(*i)++;
}

int	count_word(char *s, char c)
{
	int	size;
	int	i;
	int	flag;

	flag = 0;
	i = 0;
	size = 0;
	while (s && s[i] != '\0')
	{
		if (s[i] != '\0' && flag == 0 && (s[i] == '\'' || s[i] == '"'))
			quotes_func(s, &i, &size, &flag);
		if (s[i] != '\0' && s[i] != c && s[i] != '\'' && s[i] != '"')
		{
			scape(s, &i, &size, c);
			flag = 0;
			i--;
		}
		if (s[i] != '\0')
			i++;
	}
	return (size);
}
