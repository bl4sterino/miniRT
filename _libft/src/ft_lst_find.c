/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lst_find.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pberne <pberne@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/07 11:50:52 by pberne            #+#    #+#             */
/*   Updated: 2026/01/16 09:51:47 by pberne           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/// @brief Iterates through a list and tries to find a matching content
/// @param ft_cmp Comparison function for the desired type
/// @param cmp_value content we are serarching a match for
/// @return list node addr if content is found, or 0
t_list	*ft_lst_find(t_list *lst, int (*ft_cmp)(void *, void *),
		void *cmp_value)
{
	while (lst)
	{
		if (ft_cmp(lst->content, cmp_value))
			return (lst);
		lst = lst->next;
	}
	return (0);
}
