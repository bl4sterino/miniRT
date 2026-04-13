/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pberne <pberne@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/31 21:42:29 by pberne            #+#    #+#             */
/*   Updated: 2025/11/08 09:59:27 by pberne           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	unsigned char	*start;
	unsigned char	uc;
	size_t			i;

	uc = (unsigned char)c;
	i = 0;
	start = (unsigned char *)s;
	while (i < n)
	{
		if (start[i] == uc)
			return ((void *)(start + i));
		i++;
	}
	return (0);
}
