/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pberne <pberne@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/01 22:18:51 by pberne            #+#    #+#             */
/*   Updated: 2026/01/16 10:24:15 by pberne           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	size_t	size;
	size_t	i;
	size_t	j;
	char	*str;

	i = 0;
	size = ft_strlen((char *)s1) + ft_strlen((char *)s2);
	str = malloc(size + 1);
	if (!str)
		return (0);
	str[size] = '\0';
	while (s1[i])
	{
		str[i] = s1[i];
		i++;
	}
	j = 0;
	while (s2[j])
	{
		str[i + j] = s2[j];
		j++;
	}
	return (str);
}

char	*ft_strjoin_gc_id(char const *s1, char const *s2, int id)
{
	size_t	size;
	size_t	i;
	size_t	j;
	char	*str;

	i = 0;
	if (!s1)
		s1 = "";
	if (!s2)
		s2 = "";
	size = ft_strlen((char *)s1) + ft_strlen((char *)s2);
	str = ft_malloc_id(size + 1, id);
	str[size] = '\0';
	while (s1[i])
	{
		str[i] = s1[i];
		i++;
	}
	j = 0;
	while (s2[j])
	{
		str[i + j] = s2[j];
		j++;
	}
	return (str);
}

char	*ft_strjoin_gc(char const *s1, char const *s2)
{
	return (ft_strjoin_gc_id(s1, s2, 0));
}
