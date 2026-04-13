/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_has_suffix.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pberne <pberne@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/05 21:54:29 by pberne            #+#    #+#             */
/*   Updated: 2025/12/06 20:06:36 by pberne           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_has_suffix(char *str, char *suffix)
{
	size_t	suffix_size;
	size_t	str_size;

	str_size = ft_strlen(str);
	suffix_size = ft_strlen(str);
	if (str_size < suffix_size)
		return (0);
	else if (ft_strnstr(str + str_size - suffix_size, suffix, suffix_size))
		return (1);
	return (0);
}
