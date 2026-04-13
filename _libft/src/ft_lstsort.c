/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstsort.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pberne <pberne@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/16 09:53:07 by pberne            #+#    #+#             */
/*   Updated: 2026/02/27 17:19:00 by tpotier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_get_prev(t_list *begin_list, t_list *el)
{
	t_list	*elprev;

	elprev = begin_list;
	if (el == begin_list)
		elprev = 0;
	else
	{
		while (elprev->next != el)
			elprev = elprev->next;
	}
	return (elprev);
}

void	ft_list_swap(t_list **begin_list, t_list *el1, t_list *el2)
{
	t_list	*el1prev;
	t_list	*el2prev;
	t_list	*next;

	el1prev = ft_get_prev(*begin_list, el1);
	el2prev = ft_get_prev(*begin_list, el2);
	if (el1prev)
	{
		el1 = el1prev->next;
		el1prev->next = el2;
	}
	else
	{
		el1 = *begin_list;
		*begin_list = el2;
	}
	el2prev->next = el1;
	next = el1->next;
	el1->next = el2->next;
	el2->next = next;
}

void	ft_lstsort(t_list **begin_list, int (*cmp)(void *, void *))
{
	t_list	*curr;
	t_list	*next;
	t_list	*cmpr;
	t_list	*cmprnext;

	curr = *begin_list;
	while (curr && curr->next)
	{
		next = curr->next;
		cmpr = next;
		while (cmpr)
		{
			cmprnext = cmpr->next;
			if ((*cmp)(curr->content, cmpr->content) > 0)
			{
				ft_list_swap(begin_list, curr, cmpr);
				next = cmpr;
				break ;
			}
			cmpr = cmprnext;
		}
		curr = next;
	}
}
