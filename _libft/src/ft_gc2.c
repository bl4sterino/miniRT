/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_gc2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pberne <pberne@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/24 16:05:13 by pberne            #+#    #+#             */
/*   Updated: 2026/01/16 09:51:38 by pberne           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_gc.h"
#include "libft.h"

void	*ft_malloc(unsigned long size)
{
	return (ft_gc(GC_ALLOC, size, 0));
}

void	ft_free(void *ptr)
{
	ft_gc(GC_FREE, (uintptr_t)ptr, 0);
}

void	ft_clear_gc(void)
{
	ft_gc(GC_CLEARALL, 0, 0);
}

void	ft_gc_print_count(void)
{
	ft_gc(GC_PRINT_COUNT, 0, 0);
}

void	ft_gc_do_print_count(t_gc_node **hash_table, int id)
{
	size_t		i;
	size_t		count;
	t_gc_node	*temp;

	i = 0;
	count = 0;
	while (i < GC_HASHTABLE_SIZE)
	{
		temp = hash_table[i];
		while (temp)
		{
			if (id == 0 || id == temp->id)
				count++;
			temp = temp->next;
		}
		i++;
	}
	ft_printf("GC count : %l\n", count);
}
