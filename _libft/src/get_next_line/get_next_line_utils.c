/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pberne <pberne@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/29 08:45:00 by pberne            #+#    #+#             */
/*   Updated: 2025/12/06 01:47:35 by pberne           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/get_next_line.h"
#include "../includes/libft.h"

char	*ft_gnl_strjoin(char const *s1, char const *s2, size_t size1,
		size_t size2)
{
	size_t	size;
	size_t	i;
	size_t	j;
	char	*str;

	i = 0;
	size = size1 + size2;
	str = malloc(size + 1);
	if (!str)
		return (0);
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

t_gnl_data	*ft_add_gnl_data(int fd, t_gnl_data **data)
{
	t_gnl_data	*new;

	new = malloc(sizeof(t_gnl_data));
	if (!new)
		return (0);
	new->buff = malloc(BUFFER_SIZE);
	if (!new->buff)
	{
		free(new);
		return (0);
	}
	new->next = *data;
	new->fd = fd;
	new->pos = 0;
	new->size = 0;
	*data = new;
	return (new);
}

t_gnl_data	*ft_get_gnl_data(int fd, t_gnl_data **data)
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
	return (ft_add_gnl_data(fd, data));
}

void	ft_clear_gnl_fd(int fd, t_gnl_data **data)
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
			free(tmp->buff);
			free(tmp);
			return ;
		}
		prev = tmp;
		tmp = tmp->next;
	}
}

char	*ft_gnl_substr(char *str, int start, unsigned long size)
{
	unsigned long	i;
	char			*out;

	out = malloc(size + 1);
	if (out == 0)
		return (out);
	i = 0;
	while (i < size)
	{
		out[i] = str[start + i];
		i++;
	}
	out[i] = '\0';
	return (out);
}
