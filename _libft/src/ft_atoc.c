/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pberne <pberne@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/01 09:56:35 by pberne            #+#    #+#             */
/*   Updated: 2026/01/21 12:09:28 by pberne           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/// @brief Expects a null terminated string containing only a viable unsigned
/// char
/// @param out Assigns out to the value of the parsed char
int	ft_atouc_safe(const char *str, unsigned char *out)
{
	int	i;
	int	number;

	i = 0;
	number = 0;
	*out = 0;
	while (str[i] == ' ' || (str[i] >= 9 && str[i] <= 13))
		i++;
	while (str[i] == '+')
		i++;
	while (str[i] >= '0' && str[i] <= '9')
	{
		number = number * 10 + str[i] - '0';
		if (number > 255)
		{
			return (0);
		}
		i++;
	}
	if (str[i])
		return (0);
	*out = (unsigned char)number;
	return (1);
}

int	ft_atoc_safe(char *str, int *out)
{
	int		sign;
	long	number;

	*out = 0;
	sign = 1;
	number = 0;
	while (*str == '-' || *str == '+')
	{
		if (*str == '-')
			sign *= -1;
		str++;
	}
	while (*str >= '0' && *str <= '9')
	{
		number *= 10;
		number += *str - '0';
		if (number * sign > 127 || number * sign < -128)
			return (0);
		str++;
	}
	if (*str != '\0')
		return (0);
	*out = number * sign;
	return (1);
}
