/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_gc.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pberne <pberne@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/01 22:58:29 by pberne            #+#    #+#             */
/*   Updated: 2026/01/16 09:54:58 by pberne           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	**ft_malloc_split_gc_id(int depth, int id)
{
	char	**out;

	out = ft_malloc_id(sizeof(char *) * (depth + 1), id);
	out[depth] = 0;
	return (out);
}

char	**ft_split_r_gc(char *str, char c, t_v2i index_depth, int id)
{
	char	**out;
	int		start;
	int		end;

	if (!str)
	{
		out = ft_malloc_id(sizeof(char *), id);
		out[0] = NULL;
		return (out);
	}
	while (str[index_depth.x] && str[index_depth.x] == c)
		index_depth.x++;
	if (!str[index_depth.x])
		return (ft_malloc_split_gc_id(index_depth.y, id));
	start = index_depth.x;
	while (str[index_depth.x] && str[index_depth.x] != c)
		index_depth.x++;
	end = index_depth.x;
	out = ft_split_r_gc(str, c, (t_v2i){index_depth.x, index_depth.y + 1}, id);
	out[index_depth.y] = ft_substr_gc_id(str, start, end - start, id);
	return (out);
}

char	**ft_split_gc(char const *s, char c)
{
	return (ft_split_r_gc((char *)s, c, (t_v2i){0, 0}, 0));
}

void	ft_free_split_gc(char **tab)
{
	int	i;

	i = 0;
	while (tab[i])
	{
		ft_free(tab[i]);
		i++;
	}
	ft_free(tab);
}

char	**ft_split_gc_id(char const *s, char c, int id)
{
	return (ft_split_r_gc((char *)s, c, (t_v2i){0, 0}, id));
}
