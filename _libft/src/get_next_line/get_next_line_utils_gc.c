/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils_gc.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pberne <pberne@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/29 08:45:00 by pberne            #+#    #+#             */
/*   Updated: 2026/01/16 10:24:36 by pberne           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/get_next_line.h"
#include "../includes/libft.h"

char	*ft_gnl_strjoin_gc(char const *s1, char const *s2, size_t size1,
		size_t size2)//
{
	size_t	size;
	size_t	i;
	size_t	j;
	char	*str;

	i = 0;
	size = size1 + size2;
	str = ft_malloc(size + 1);
	str[size] = '\0';
	while (i < size1)
	{
		str[i] = s1[i];
		i++;
	}
	j = 0;
	while (j < size2)
	{
		str[i + j] = s2[j];
		j++;
	}
	return (str);
}

t_gnl_data	*ft_add_gnl_data_gc(int fd, t_gnl_data **data)
{
	t_gnl_data	*new;

	new = ft_malloc(sizeof(t_gnl_data));
	new->buff = ft_malloc(BUFFER_SIZE);
	if (!new->buff)
	{
		ft_free(new);
		return (0);
	}
	new->next = *data;
	new->fd = fd;
	new->pos = 0;
	new->size = 0;
	*data = new;
	return (new);
}

t_gnl_data	*ft_get_gnl_data_gc(int fd, t_gnl_data **data)
{
	t_gnl_data	*dat;

	dat = *data;
	if (dat)
	{
		while (dat)
		{
			if (dat->fd == fd)
				return (dat);
			dat = dat->next;
		}
	}
	return (ft_add_gnl_data_gc(fd, data));
}

void	ft_clear_gnl_fd_gc(int fd, t_gnl_data **data)
{
	t_gnl_data	*tmp;
	t_gnl_data	*prev;

	prev = 0;
	tmp = *data;
	while (tmp)
	{
		if (tmp->fd == fd)
		{
			if (prev)
				prev->next = tmp->next;
			else
				*data = tmp->next;
			ft_free(tmp->buff);
			ft_free(tmp);
			return ;
		}
		prev = tmp;
		tmp = tmp->next;
	}
}

char	*ft_gnl_substr_gc(char *str, int start, unsigned long size)
{
	unsigned long	i;
	char			*out;

	out = ft_malloc(size + 1);
	i = 0;
	while (i < size)
	{
		out[i] = str[start + i];
		i++;
	}
	out[i] = '\0';
	return (out);
}
