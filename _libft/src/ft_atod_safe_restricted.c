/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atod_safe_restricted.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pberne <pberne@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/21 13:38:25 by pberne            #+#    #+#             */
/*   Updated: 2026/03/04 17:33:50 by pberne           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/// makes sure the input is representing a number in range [0.0, 1.0]
int	ft_atod_safe_0_1(char *str, double *dest)
{
	if (!ft_atod_safe(str, dest))
		return (0);
	if (*dest < 0.0 || *dest > 1.0)
	{
		*dest = 0.0;
		return (0);
	}
	return (1);
}

/// parses a double in range [0, 255] and normalize it in
/// range [0, 1]
int	ft_atod_safe_0_255_to_0_1(char *str, double *dest)
{
	if (!ft_atod_safe(str, dest))
		return (0);
	if (*dest < 0.0 || *dest > 255)
	{
		*dest = 0.0;
		return (0);
	}
	*dest = *dest / 255.0;
	return (1);
}

int	ft_atof_safe(char *str, float *dest)
{
	double	d_dest;

	if (!ft_atod_safe(str, &d_dest))
		return (0);
	*dest = (float)d_dest;
	return (1);
}

int	ft_atof_safe_0_1(char *str, float *dest)
{
	if (!ft_atof_safe(str, dest))
		return (0);
	if (*dest < 0.0f || *dest > 1.0f)
	{
		*dest = 0.0f;
		return (0);
	}
	return (1);
}

int	ft_atof_safe_0_255_to_0_1(char *str, float *dest)
{
	if (!ft_atof_safe(str, dest))
		return (0);
	if (*dest < 0 || *dest > 255)
	{
		*dest = 0.0f;
		return (0);
	}
	*dest = *dest / 255.0f;
	return (1);
}
