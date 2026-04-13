/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_swap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pberne <pberne@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/07 12:09:39 by pberne            #+#    #+#             */
/*   Updated: 2025/12/07 12:57:27 by pberne           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_swapi(int *a, int *b)
{
	int	temp;

	temp = *a;
	*a = *b;
	*b = temp;
}

void	ft_swapl(long *a, long *b)
{
	long	temp;

	temp = *a;
	*a = *b;
	*b = temp;
}

void	ft_swapul(unsigned long *a, unsigned long *b)
{
	unsigned long	temp;

	temp = *a;
	*a = *b;
	*b = temp;
}

void	ft_swapf(float *a, float *b)
{
	float	temp;

	temp = *a;
	*a = *b;
	*b = temp;
}

void	ft_swapd(double *a, double *b)
{
	double	temp;

	temp = *a;
	*a = *b;
	*b = temp;
}
