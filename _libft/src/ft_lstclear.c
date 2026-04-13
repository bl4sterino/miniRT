/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pberne <pberne@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/02 21:26:32 by pberne            #+#    #+#             */
/*   Updated: 2026/01/16 09:51:51 by pberne           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void *))
{
	t_list	*temp;
	t_list	*temp2;

	temp = *lst;
	while (temp)
	{
		temp2 = temp;
		temp = temp->next;
		if (del)
			del(temp2->content);
		free(temp2);
	}
	*lst = 0;
}

void	ft_lstclear_gc(t_list **lst, void (*del)(void *))
{
	t_list	*temp;
	t_list	*temp2;

	temp = *lst;
	while (temp)
	{
		temp2 = temp;
		temp = temp->next;
		if (del)
			del(temp2->content);
		ft_free(temp2);
	}
	*lst = 0;
}
