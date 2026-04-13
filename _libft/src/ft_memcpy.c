/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pberne <pberne@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/08 09:50:15 by pberne            #+#    #+#             */
/*   Updated: 2025/11/10 10:17:30 by pberne           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	unsigned char	*dstc;
	unsigned char	*srcc;
	size_t			i;

	if (!dst && !src)
		return (dst);
	i = 0;
	dstc = (unsigned char *)dst;
	srcc = (unsigned char *)src;
	while (i < n)
	{
		dstc[i] = srcc[i];
		i++;
	}
	return (dst);
}
