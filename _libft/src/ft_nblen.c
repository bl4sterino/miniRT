/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_nblen.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pberne <pberne@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/16 09:52:54 by pberne            #+#    #+#             */
/*   Updated: 2026/01/16 09:52:57 by pberne           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
** @brief Counts the numbers in nb
** @param nb Long int to process
** @return Length of nb
*/
size_t	ft_nblen(long nb)
{
	size_t	len;

	if (nb == 0)
		return (1);
	len = 0;
	if (nb < 0)
	{
		len++;
		nb = -nb;
	}
	while (nb)
	{
		len++;
		nb /= 10;
	}
	return (len);
}
