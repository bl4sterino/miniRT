/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pberne <pberne@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/08 14:26:51 by pberne            #+#    #+#             */
/*   Updated: 2026/01/22 14:23:50 by pberne           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exit.h"
#include "libft.h"

void	ft_execute_exit_fcts(t_list *list)
{
	t_exit_data	*exit_data;

	while (list)
	{
		exit_data = (t_exit_data *)list->content;
		exit_data->f(exit_data->d);
		list = list->next;
	}
}

void	ft_do_exit(int exitcode, void *data, void (*ft_exit_fct)(void *))
{
	static t_list	*exit_list = 0;
	t_exit_data		*new_data;
	t_list			*new_list;

	if (exitcode == ADD_EXIT)
	{
		new_data = ft_malloc(sizeof(t_exit_data));
		new_list = ft_malloc(sizeof(t_list));
		new_data->d = data;
		new_data->f = ft_exit_fct;
		new_list->next = 0;
		new_list->content = new_data;
		ft_lstadd_front(&exit_list, new_list);
		return ;
	}
	ft_execute_exit_fcts(exit_list);
	get_next_line(-2);
	ft_clear_gc();
	exit(exitcode);
}

void	ft_add_exit(void *d, void (*f)(void *))
{
	ft_do_exit(ADD_EXIT, d, f);
}

/// @brief Clear gc, get_next_line and exits
/// @param exit_code DO NOT USE EXIT CODE -1
void	ft_exit(int exit_code)
{
	ft_do_exit(exit_code, 0, 0);
}

void	ft_exit_str_fd(int exit_code, char *str, int fd)
{
	ft_putstr_fd(str, fd);
	ft_exit(exit_code);
}
