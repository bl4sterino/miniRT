/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc_gc.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pberne <pberne@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/01 16:15:57 by pberne            #+#    #+#             */
/*   Updated: 2026/01/16 09:51:32 by pberne           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_calloc_full(void *ptr, size_t total, unsigned char *p)
{
	unsigned long	*pl;
	size_t			n;

	p = ptr;
	n = total;
	while (n && ((unsigned long)p % sizeof(unsigned long) != 0))
	{
		*p = 0;
		p++;
		n--;
	}
	pl = (unsigned long *)p;
	while (n >= sizeof(unsigned long))
	{
		*pl = 0UL;
		pl++;
		n -= sizeof(unsigned long);
	}
	p = (unsigned char *)pl;
	while (n)
	{
		*p = 0;
		p++;
		n--;
	}
}

void	*ft_calloc_gc_id(size_t nmemb, size_t size, int id)
{
	void	*ptr;

	if (size != 0 && nmemb > ((size_t) -1 / size))
		return (NULL);
	ptr = ft_malloc_id(nmemb * size, id);
	if (!ptr)
		return (NULL);
	ft_calloc_full(ptr, nmemb * size, 0);
	return (ptr);
}

void	*ft_calloc_gc(size_t nmemb, size_t size)
{
	return (ft_calloc_gc_id(nmemb, size, 0));
}
