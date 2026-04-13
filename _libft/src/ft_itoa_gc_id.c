/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa_gc_id.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pberne <pberne@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/02 14:47:15 by pberne            #+#    #+#             */
/*   Updated: 2026/01/16 09:51:44 by pberne           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_itoa_r_id(long n, int *total_depth, t_v2i depth_offset, int id)
{
	char	*out;

	*total_depth = depth_offset.x;
	if (n < 10)
	{
		out = ft_malloc_id(depth_offset.x + 2, id);
		out[depth_offset.x + 1] = '\0';
	}
	if (n > 9)
		out = ft_itoa_r_id(n / 10, total_depth, (t_v2i){depth_offset.x + 1,
				depth_offset.y}, id);
	out[*total_depth - depth_offset.x + depth_offset.y] = n % 10 + '0';
	return (out);
}

char	*ft_itoa_gc_id(int n, int id)
{
	long	nbr;
	char	*out;
	int		total_depth;

	total_depth = 0;
	nbr = n;
	if (nbr < 0)
	{
		nbr = -nbr;
		out = ft_itoa_r_id(nbr, &total_depth, (t_v2i){1, 1}, id);
		out[0] = '-';
		return (out);
	}
	return (ft_itoa_r_id(n, &total_depth, (t_v2i){0, 0}, id));
}
