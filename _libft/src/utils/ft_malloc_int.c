/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_malloc_int.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pberne <pberne@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/22 14:42:05 by pberne            #+#    #+#             */
/*   Updated: 2026/01/22 14:53:52 by pberne           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	*ft_malloc_int(int n)
{
	return (ft_malloc_id_int(n, 0));
}

int	*ft_malloc_id_int(int n, int malloc_id)
{
	int	*ptr;

	ptr = ft_malloc_id(sizeof(int), malloc_id);
	*ptr = n;
	return (ptr);
}
