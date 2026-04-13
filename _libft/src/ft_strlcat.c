/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pberne <pberne@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/01 15:13:51 by pberne            #+#    #+#             */
/*   Updated: 2025/11/10 10:17:10 by pberne           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t	dstlen;
	size_t	srclen;
	size_t	i;
	size_t	j;

	srclen = ft_strlen(src);
	if (size == 0)
		return (srclen);
	dstlen = ft_strlen(dst);
	if (size <= dstlen)
		return (size + srclen);
	i = dstlen;
	j = 0;
	while (i + 1 < size && src[j])
	{
		dst[i] = src[j];
		i++;
		j++;
	}
	dst[i] = '\0';
	return (dstlen + srclen);
}
