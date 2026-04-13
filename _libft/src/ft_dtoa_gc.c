/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dtoa_gc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pberne <pberne@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/01 19:23:43 by pberne            #+#    #+#             */
/*   Updated: 2026/01/16 09:51:34 by pberne           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_force_decimals(char *str, int decimals)
{
	char	*temp;
	char	*outstr;
	size_t	size;

	if (!str)
		return (0);
	size = decimals - ft_strlen(str);
	if (size > 0)
	{
		temp = ft_malloc(size + 1);
		if (!temp)
			return (0);
		temp[size] = '\0';
		ft_memset(temp, '0', size);
	}
	else
		return (str);
	outstr = ft_strjoin_gc(temp, str);
	ft_free(temp);
	ft_free(str);
	return (outstr);
}

char	*ft_dtoa_p_full(double n, int decimals, int i)
{
	char	*intstr;
	char	*decstr;
	long	intpart;
	char	*outstr;

	intpart = (long)n;
	intstr = ft_ltoa_gc(intpart);
	if (n < 0)
		n = -n;
	n -= ft_abs(intpart);
	while (i < decimals)
	{
		n *= 10;
		i++;
	}
	decstr = ft_ultoa_gc(n);
	decstr = ft_force_decimals(decstr, decimals);
	outstr = ft_strjoin_mult_gc_id(0, 3, intstr, ".", decstr);
	ft_free(intstr);
	ft_free(decstr);
	return (outstr);
}

char	*ft_dtoa_gc(double n)
{
	return (ft_dtoa_p_full(n, DOUBLE_PRINT_PRECISION, 0));
}

char	*ft_dtoa_p_gc(double n, int decimals)
{
	return (ft_dtoa_p_full(n, decimals, 0));
}
