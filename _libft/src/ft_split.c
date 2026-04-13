/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pberne <pberne@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/01 22:58:29 by pberne            #+#    #+#             */
/*   Updated: 2025/11/29 17:46:32 by pberne           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_free_split(char **tab)
{
	int	i;

	i = 0;
	while (tab[i])
	{
		free(tab[i]);
		i++;
	}
	free(tab);
}

char	**ft_malloc_split(int depth)
{
	char	**out;

	out = malloc(sizeof(char *) * (depth + 1));
	if (!out)
		return (0);
	out[depth] = 0;
	return (out);
}

char	**ft_split_r(char *str, char c, int index, int depth)
{
	char	**out;
	int		start;
	int		end;

	while (str[index] && str[index] == c)
		index++;
	if (!str[index])
		return (ft_malloc_split(depth));
	start = index;
	while (str[index] && str[index] != c)
		index++;
	end = index;
	out = ft_split_r(str, c, index, depth + 1);
	if (!out)
		return (0);
	out[depth] = ft_substr(str, start, end - start);
	if (!out[depth])
		return (0);
	return (out);
}

char	**ft_split(char const *s, char c)
{
	return (ft_split_r((char *)s, c, 0, 0));
}
