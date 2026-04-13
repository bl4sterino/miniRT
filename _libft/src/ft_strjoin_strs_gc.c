/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin_strs_gc.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pberne <pberne@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/01 22:18:51 by pberne            #+#    #+#             */
/*   Updated: 2026/01/16 10:24:12 by pberne           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_join_strs_gc_id(char **tab, char *sep, int id)
{
	size_t	size;
	size_t	i;
	size_t	j;
	char	*dest;

	if (!tab || !tab[0])
		return (0);
	size = 0;
	i = -1;
	while (tab[++i])
		size += ft_strlen(tab[i]);
	if (!sep)
		sep = "";
	dest = ft_malloc_id(size + (i - 1) * ft_strlen(sep) + 1, id);
	dest[size + (i - 1) * ft_strlen(sep)] = '\0';
	j = 0;
	size = 0;
	while (j < i)
	{
		size += ft_strlcpy(dest + size, tab[j], ft_strlen(tab[j]) + 1);
		if (j + 1 < i)
			size += ft_strlcpy(dest + size, sep, ft_strlen(sep) + 1);
		j++;
	}
	return (dest);
}

char	*ft_join_strs_gc(char **tab, char *separator)
{
	return (ft_join_strs_gc_id(tab, separator, 0));
}
