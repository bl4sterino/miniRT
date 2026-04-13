/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pberne <pberne@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/02 18:48:55 by pberne            #+#    #+#             */
/*   Updated: 2026/01/16 09:53:13 by pberne           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstnew(void *content)
{
	t_list	*new;

	new = malloc(sizeof(t_list));
	if (!new)
		return (0);
	new->next = 0;
	new->content = content;
	return (new);
}

t_list	*ft_lstnew_gc_id(void *content, int id)
{
	t_list	*new;

	new = ft_malloc_id(sizeof(t_list), id);
	new->next = 0;
	new->content = content;
	return (new);
}

t_list	*ft_lstnew_gc(void *content)
{
	return (ft_lstnew_gc_id(content, 0));
}
