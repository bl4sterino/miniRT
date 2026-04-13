/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free_batch.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pberne <pberne@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/14 15:23:03 by pberne            #+#    #+#             */
/*   Updated: 2025/12/08 17:44:55 by pberne           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdarg.h>

/// @brief Frees the given quantity of pointers and returns ret
/// @param ret The return value
/// @param nb The number of pointers to free
long	ft_free_batch(long ret, int nb, ...)
{
	va_list	ap;
	int		i;

	i = 0;
	va_start(ap, nb);
	while (i < nb)
	{
		free(va_arg(ap, void *));
		i++;
	}
	va_end(ap);
	return (ret);
}

long	ft_free_batch_gc(long ret, int nb, ...)
{
	va_list	ap;
	int		i;

	i = 0;
	va_start(ap, nb);
	while (i < nb)
	{
		ft_free(va_arg(ap, void *));
		i++;
	}
	va_end(ap);
	return (ret);
}
