/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pberne <pberne@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/01 09:56:35 by pberne            #+#    #+#             */
/*   Updated: 2026/01/21 09:05:38 by pberne           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_atoi(const char *str)
{
	int	sign;
	int	i;
	int	number;

	i = 0;
	sign = 1;
	number = 0;
	while (str[i] == ' ' || (str[i] >= 9 && str[i] <= 13))
		i++;
	if (str[i] == '+')
		i++;
	else if (str[i] == '-')
	{
		sign = -1;
		i++;
	}
	while (str[i] >= '0' && str[i] <= '9')
	{
		number = number * 10 + str[i] - '0';
		i++;
	}
	return (number * sign);
}

int	ft_find_base_value(char *base, char c)
{
	int	i;

	i = 0;
	while (base[i] != c)
	{
		i++;
	}
	return (i);
}

int	ft_atoi_base(const char *str, char *base)
{
	int	sign;
	int	i;
	int	number;
	int	baselen;

	baselen = ft_strlen(base);
	i = 0;
	sign = 1;
	number = 0;
	while (str[i] == ' ' || (str[i] >= 9 && str[i] <= 13))
		i++;
	if (str[i] == '+')
		i++;
	else if (str[i] == '-')
	{
		sign = -1;
		i++;
	}
	while (ft_strchr(base, str[i]))
	{
		number = number * baselen + ft_find_base_value(base, str[i]);
		i++;
	}
	return (number * sign);
}

/// @brief Parses str and assigns its value to out
/// @return 0 on failure, 1 on success
int	ft_atoi_safe(char *str, int *out)
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
		if (number * sign > 2147483647 || number * sign < -2147483647)
			return (0);
		str++;
	}
	if (*str != '\0')
		return (0);
	*out = number * sign;
	return (1);
}
