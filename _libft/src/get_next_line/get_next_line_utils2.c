/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils2.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pberne <pberne@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/28 16:48:41 by pberne            #+#    #+#             */
/*   Updated: 2026/01/16 10:24:40 by pberne           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/get_next_line.h"
#include "../includes/libft.h"

void	ft_clear_all_gnl_data(t_gnl_data **data)
{
	t_gnl_data	*tmp;
	t_gnl_data	*prev;

	prev = *data;
	tmp = *data;
	while (tmp)
	{
		tmp = tmp->next;
		free(prev->buff);
		free(prev);
		prev = tmp;
	}
	*data = 0;
}

char	*get_next_line_no_nl(int fd)
{
	char			*line;
	unsigned long	len;

	len = 0;
	line = get_next_line_count(fd, &len);
	if (line)
	{
		len = ft_strlen(line);
		if (line[len - 1] == '\n')
			line[len - 1] = '\0';
	}
	return (line);
}
