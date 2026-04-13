/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pberne <pberne@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/01 16:15:57 by pberne            #+#    #+#             */
/*   Updated: 2025/11/08 10:35:05 by pberne           ###   ########.fr       */
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

void	*ft_calloc(size_t nmemb, size_t size)
{
	void	*ptr;

	if (size != 0 && nmemb > ((size_t) -1 / size))
		return (NULL);
	ptr = malloc(nmemb * size);
	if (!ptr)
		return (NULL);
	ft_calloc_full(ptr, nmemb * size, 0);
	return (ptr);
}
