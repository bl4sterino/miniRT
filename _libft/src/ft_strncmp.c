/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pberne <pberne@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/31 16:48:37 by pberne            #+#    #+#             */
/*   Updated: 2026/01/16 10:24:19 by pberne           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t	i;

	i = 0;
	while (i < n)
	{
		if (!s1[i] || s1[i] != s2[i])
			return ((unsigned char)s1[i] - (unsigned char)s2[i]);
		i++;
	}
	return (0);
}

/// Compares at most sizes.x bytes
/// s1 len is sizes.y
/// s2 len is sizes.z
int	ft_strcmp_size(const char *s1, const char *s2, t_v3ul sizes)
{
	size_t	i;

	i = 0;
	if (sizes.y != sizes.x || sizes.z != sizes.x)
		return (-1);
	while (i < sizes.x)
	{
		if (s1[i] != s2[i])
			return ((unsigned char)s1[i] - (unsigned char)s2[i]);
		i++;
	}
	return (0);
}
