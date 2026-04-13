/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dtoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pberne <pberne@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/01 19:23:43 by pberne            #+#    #+#             */
/*   Updated: 2025/12/02 20:46:54 by pberne           ###   ########.fr       */
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
		temp = malloc(size + 1);
		if (!temp)
			return (0);
		temp[size] = '\0';
		ft_memset(temp, '0', size);
	}
	else
		return (str);
	outstr = ft_strjoin(temp, str);
	free(temp);
	free(str);
	return (outstr);
}

char	*ft_dtoa_p_full(double n, int decimals, int i)
{
	char	*intstr;
	char	*decstr;
	long	intpart;
	char	*outstr;

	intpart = (long)n;
	intstr = ft_ltoa(intpart);
	if (!intstr)
		return (0);
	if (n < 0)
		n = -n;
	n -= ft_abs(intpart);
	while (i < decimals)
	{
		n *= 10;
		i++;
	}
	decstr = ft_ultoa(n);
	decstr = ft_force_decimals(decstr, decimals);
	if (!decstr)
		return ((char *)ft_free_batch(0, 1, intstr));
	outstr = ft_strjoin_mult(3, intstr, ".", decstr);
	free(intstr);
	free(decstr);
	return (outstr);
}

char	*ft_dtoa(double n)
{
	return (ft_dtoa_p_full(n, DOUBLE_PRINT_PRECISION, 0));
}

char	*ft_dtoa_p(double n, int decimals)
{
	return (ft_dtoa_p_full(n, decimals, 0));
}
