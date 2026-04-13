/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_gc.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pberne <pberne@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/24 14:13:08 by pberne            #+#    #+#             */
/*   Updated: 2026/01/16 09:51:24 by pberne           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_GC_H
# define FT_GC_H

# include <stdint.h>
# include <stdlib.h>

enum					e_gc_flags
{
	GC_ALLOC,
	GC_FREE,
	GC_CLEARALL,
	GC_PRINT_COUNT
};

# define GC_HASHTABLE_SIZE 16411

typedef struct s_gc_node
{
	int					id;
	void				*ptr;
	struct s_gc_node	*next;
}						t_gc_node;

void					*ft_gc(int flag, uintptr_t size, int id);
void					*ft_malloc(unsigned long size);
void					ft_free(void *ptr);

void					ft_gc_print_count(void);
void					ft_gc_print_count_id(int id);

void					*ft_malloc_id(unsigned long size, int id);
void					ft_clear_gc_id(int id);

void					ft_clear_gc(void);

#endif
