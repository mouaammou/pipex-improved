/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_proc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mouaammo <mouaammo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/20 16:20:36 by mouaammo          #+#    #+#             */
/*   Updated: 2022/12/20 18:29:48 by mouaammo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

char	**ft_split_proc(char *s, char c)
{
	char	**split;
	int		size;

	if (!s)
		return (NULL);
	size = count_word(s, c);
	split = (char **) malloc(sizeof (char *) * size + 1);
	if (!split)
		return (NULL);
	split[size] = 0;
	return (split_improved(s, c, split));
}
