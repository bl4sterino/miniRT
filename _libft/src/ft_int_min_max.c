/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_int_min_max.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pberne <pberne@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/17 17:37:06 by pberne            #+#    #+#             */
/*   Updated: 2025/12/07 17:04:08 by pberne           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_min(int a, int b)
{
	if (a < b)
		return (a);
	return (b);
}

int	ft_max(int a, int b)
{
	if (a > b)
		return (a);
	return (b);
}

int	ft_minv(unsigned int count, ...)
{
	va_list			ap;
	unsigned int	i;
	int				min;
	int				temp;

	i = 0;
	min = 0;
	temp = 0;
	va_start(ap, count);
	while (i < count)
	{
		temp = va_arg(ap, int);
		if (i == 0 || temp < min)
			min = temp;
		i++;
	}
	va_end(ap);
	return (min);
}

int	ft_maxv(unsigned int count, ...)
{
	va_list			ap;
	unsigned int	i;
	int				max;
	int				temp;

	i = 0;
	max = 0;
	temp = 0;
	va_start(ap, count);
	while (i < count)
	{
		temp = va_arg(ap, int);
		if (i == 0 || temp > max)
			max = temp;
		i++;
	}
	va_end(ap);
	return (max);
}
