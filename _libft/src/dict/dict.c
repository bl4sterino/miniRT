/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dict.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pberne <pberne@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/21 07:50:53 by pberne            #+#    #+#             */
/*   Updated: 2026/01/21 09:12:46 by pberne           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static t_dict	*ft_dict_new_gc_id(char *key, void *value, int id)
{
	t_dict	*new_node;

	new_node = ft_malloc_id(sizeof(t_dict), id);
	if (!new_node)
		return (NULL);
	new_node->key = ft_strdup_gc_id(key, id);
	new_node->value = value;
	new_node->next = NULL;
	return (new_node);
}

void	ft_dict_set_gc_id(t_dict **dict, char *key, void *value, int id)
{
	t_dict	*current;
	t_dict	*new_node;

	if (!dict || !key)
		return ;
	current = *dict;
	while (current)
	{
		if (ft_strcmp(current->key, key) == 0)
		{
			current->value = value;
			return ;
		}
		current = current->next;
	}
	new_node = ft_dict_new_gc_id(key, value, id);
	if (new_node)
	{
		new_node->next = *dict;
		*dict = new_node;
	}
}

void	ft_dict_set(t_dict **dict, char *key, void *value)
{
	ft_dict_set_gc_id(dict, key, value, 0);
}

void	*ft_dict_get(t_dict *dict, char *key)
{
	if (!key)
		return (NULL);
	while (dict)
	{
		if (ft_strcmp(dict->key, key) == 0)
			return (dict->value);
		dict = dict->next;
	}
	return (NULL);
}

int	ft_dict_try_get(t_dict *dict, char *key, void **out)
{
	if (!key)
		return (0);
	while (dict)
	{
		if (ft_strcmp(dict->key, key) == 0)
		{
			if (out)
				*out = dict->value;
			return (1);
		}
		dict = dict->next;
	}
	return (0);
}
