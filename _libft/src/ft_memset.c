/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pberne <pberne@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/01 10:16:27 by pberne            #+#    #+#             */
/*   Updated: 2025/12/01 19:13:48 by pberne           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *s, int c, size_t n)
{
	unsigned char	ch;
	unsigned char	*str;
	size_t			i;

	i = 0;
	str = (unsigned char *)s;
	ch = (unsigned char)c;
	while (i < n)
	{
		str[i] = ch;
		i++;
	}
	return (s);
}

/// @brief n is the number of ints not teh byte size
void	*ft_memset_int(void *p, int c, size_t n)
{
	size_t	i;
	size_t	nl;
	long	*pl;
	long	combined;

	i = 0;
	nl = n / 2;
	pl = (long *)p;
	combined = c;
	combined = (combined << 32) | (c & 0x00000000FFFFFFFF);
	while (i < nl)
	{
		pl[i] = combined;
		i++;
	}
	if (n % 2 != 0 && n > 0)
		((int *)p)[n - 1] = c;
	return (p);
}
