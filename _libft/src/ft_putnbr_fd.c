/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pberne <pberne@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/02 16:43:45 by pberne            #+#    #+#             */
/*   Updated: 2026/02/27 17:17:14 by tpotier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putnbr_fdl(long n, int fd)
{
	char	c;

	if (n < 0)
	{
		n = -n;
		ft_write_all(fd, "-", 1);
	}
	if (n > 9)
		ft_putnbr_fdl(n / 10, fd);
	c = '0' + n % 10;
	ft_write_all(fd, &c, 1);
}

void	ft_putnbr_fd(int n, int fd)
{
	ft_putnbr_fdl(n, fd);
}
