/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putdouble.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pberne <pberne@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/30 15:05:01 by pberne            #+#    #+#             */
/*   Updated: 2025/11/30 16:31:02 by pberne           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_putdouble(double n)
{
	return (ft_putdouble_p(n, DOUBLE_PRINT_PRECISION));
}

int	ft_putdouble_p(double n, int decimals)
{
	long	int_part;
	double	frac_part;
	int		count;
	int		i;

	i = 0;
	count = 0;
	if (n < 0)
	{
		count += write(1, "-", 1);
		n = -n;
	}
	int_part = (long)n;
	count += ft_putnbr_base_l(int_part, "0123456789");
	count += write(1, ".", 1);
	frac_part = n - (double)int_part;
	while (i < decimals)
	{
		frac_part *= 10;
		count += ft_putnbr_base_l((long)frac_part, "0123456789");
		frac_part -= (long)frac_part;
		i++;
	}
	return (count);
}
