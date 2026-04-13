/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa_gc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pberne <pberne@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/02 14:47:15 by pberne            #+#    #+#             */
/*   Updated: 2026/01/22 11:15:14 by pberne           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_itoa_r(long n, int depth, int *total_depth, int offset)
{
	char	*out;

	*total_depth = depth;
	if (n < 10)
	{
		out = ft_malloc(depth + 2);
		out[depth + 1] = '\0';
	}
	if (n > 9)
		out = ft_itoa_r(n / 10, depth + 1, total_depth, offset);
	out[*total_depth - depth + offset] = n % 10 + '0';
	return (out);
}

char	*ft_itoa_gc(int n)
{
	return (ft_itoa_gc_id(n, 0));
}

char	*ft_ltoa_gc(long n)
{
	long	nbr;
	char	*out;
	int		total_depth;

	total_depth = 0;
	nbr = n;
	if (nbr < 0)
	{
		nbr = -nbr;
		out = ft_itoa_r(nbr, 1, &total_depth, 1);
		out[0] = '-';
		return (out);
	}
	return (ft_itoa_r(n, 0, &total_depth, 0));
}

char	*ft_ultoa_r(long n, int depth, int *total_depth, int offset)
{
	char	*out;

	*total_depth = depth;
	if (n < 10)
	{
		out = ft_malloc(depth + 2);
		out[depth + 1] = '\0';
	}
	if (n > 9)
		out = ft_ultoa_r(n / 10, depth + 1, total_depth, offset);
	out[*total_depth - depth + offset] = n % 10 + '0';
	return (out);
}

char	*ft_ultoa_gc(unsigned long n)
{
	int	total_depth;

	total_depth = 0;
	return (ft_ultoa_r(n, 0, &total_depth, 0));
}
