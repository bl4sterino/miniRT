/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstdelone_fr.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pberne <pberne@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/16 09:52:05 by pberne            #+#    #+#             */
/*   Updated: 2026/01/19 12:02:00 by pberne           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/// @brief Iterates through a list and deletes the matching elem if it exists
/// @param lst List to iterate
/// @param elem content we are looking to delete
/// @param del function to apply to the content of the elen
/// @return void
void	ft_lstdelone_fr(t_list **lst, t_list *elem, void (*del)(void *))
{
	t_list	*check;

	if (!*lst || !elem)
		return ;
	check = *lst;
	if (check != elem)
	{
		while ((check)->next != elem)
			check = check->next;
		check->next = elem->next;
	}
	else if (!elem->next)
		*lst = NULL;
	else
		*lst = elem->next;
	if (del)
		del(elem->content);
	elem->content = NULL;
	free(elem);
}

void	ft_lstdelone_fr_gc(t_list **lst, t_list *elem, void (*del)(void *))
{
	t_list	*check;

	if (!*lst || !elem)
		return ;
	check = *lst;
	if (check != elem)
	{
		while ((check)->next != elem)
			check = check->next;
		check->next = elem->next;
	}
	else if (!elem->next)
		*lst = NULL;
	else
		*lst = elem->next;
	if (del)
		del(elem->content);
	elem->content = NULL;
	ft_free(elem);
}
