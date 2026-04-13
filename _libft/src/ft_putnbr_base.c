/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_base.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pberne <pberne@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/23 10:58:12 by pberne            #+#    #+#             */
/*   Updated: 2026/02/27 17:46:11 by tpotier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_put_nbr_base_l_r(long n, char *base, int baselen, int *count)
{
	if (n >= baselen)
		ft_put_nbr_base_l_r(n / baselen, base, baselen, count);
	*count += ft_write_all(1, base + (n % baselen), 1);
}

/// Doesnt check base, returns number of printed characters
int	ft_putnbr_base_l(long n, char *base)
{
	int	baselen;
	int	count;
	int	n_dived;

	baselen = ft_strlen(base);
	count = 0;
	n_dived = n / baselen;
	if (n < 0)
	{
		count += write(1, "-", 1);
		n_dived = -n_dived;
	}
	if (n >= baselen || n <= -baselen)
		ft_put_nbr_base_l_r(n_dived, base, baselen, &count);
	count += ft_write_all(1, base + ft_abs((n % baselen)), 1);
	return (count);
}

void	ft_put_nbr_base_ul_r(unsigned long n, char *base, unsigned int baselen,
		int *count)
{
	if (n >= baselen)
		ft_put_nbr_base_ul_r(n / baselen, base, baselen, count);
	*count += ft_write_all(1, base + (n % baselen), 1);
}

int	ft_putnbr_base_ul(unsigned long n, char *base)
{
	int				count;
	unsigned int	baselen;

	count = 0;
	baselen = ft_strlen(base);
	if (n >= baselen)
		ft_put_nbr_base_ul_r(n / baselen, base, baselen, &count);
	count += ft_write_all(1, base + (n % baselen), 1);
	return (count);
}
