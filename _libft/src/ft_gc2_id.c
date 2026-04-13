/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_gc2_id.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pberne <pberne@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/24 16:05:13 by pberne            #+#    #+#             */
/*   Updated: 2026/01/16 09:51:37 by pberne           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_gc.h"
#include "libft.h"

void	*ft_malloc_id(unsigned long size, int id)
{
	return (ft_gc(GC_ALLOC, size, id));
}

void	ft_clear_gc_id(int id)
{
	ft_gc(GC_CLEARALL, 0, id);
}

void	ft_gc_print_count_id(int id)
{
	ft_gc(GC_PRINT_COUNT, 0, id);
}
