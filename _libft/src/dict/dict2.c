/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dict2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pberne <pberne@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/21 07:50:53 by pberne            #+#    #+#             */
/*   Updated: 2026/01/21 09:12:44 by pberne           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_dict_remove(t_dict **dict, char *key)
{
	t_dict	*current;
	t_dict	*prev;

	if (!dict || !*dict || !key)
		return ;
	current = *dict;
	prev = NULL;
	while (current)
	{
		if (ft_strcmp(current->key, key) == 0)
		{
			if (prev)
				prev->next = current->next;
			else
				*dict = current->next;
			ft_free(current->key);
			ft_free(current);
			return ;
		}
		prev = current;
		current = current->next;
	}
}
