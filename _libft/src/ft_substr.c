/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pberne <pberne@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/01 17:28:42 by pberne            #+#    #+#             */
/*   Updated: 2026/01/16 10:24:33 by pberne           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(const char *str, unsigned int start, size_t len)
{
	size_t	str_len;
	size_t	i;
	char	*out;

	str_len = ft_strlen(str);
	if (start >= str_len)
		len = 0;
	else if (start + len > str_len)
		len = str_len - start;
	out = malloc(len + 1);
	if (out == 0)
		return (out);
	i = 0;
	while (i < len)
	{
		out[i] = str[start + i];
		i++;
	}
	out[i] = '\0';
	return (out);
}

char	*ft_substr_gc(const char *str, unsigned int start, size_t len)
{
	return (ft_substr_gc_id(str, start, len, 0));
}

char	*ft_substr_gc_id(const char *str, unsigned int start, size_t len,
		int id)
{
	size_t	str_len;
	size_t	i;
	char	*out;

	str_len = ft_strlen(str);
	if (start >= str_len)
		len = 0;
	else if (start + len > str_len)
		len = str_len - start;
	out = ft_malloc_id(len + 1, id);
	i = 0;
	while (i < len)
	{
		out[i] = str[start + i];
		i++;
	}
	out[i] = '\0';
	return (out);
}
