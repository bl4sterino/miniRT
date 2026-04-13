/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils2_gc.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pberne <pberne@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/28 16:48:41 by pberne            #+#    #+#             */
/*   Updated: 2025/12/08 19:12:56 by pberne           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/get_next_line.h"
#include "../includes/libft.h"

void	ft_clear_all_gnl_data_gc(t_gnl_data **data)
{
	t_gnl_data	*tmp;
	t_gnl_data	*prev;

	prev = *data;
	tmp = *data;
	while (tmp)
	{
		tmp = tmp->next;
		ft_free(prev->buff);
		ft_free(prev);
		prev = tmp;
	}
	*data = 0;
}
