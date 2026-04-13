/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pberne <pberne@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/29 08:44:37 by pberne            #+#    #+#             */
/*   Updated: 2025/11/29 17:46:59 by pberne           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/get_next_line.h"
#include "../includes/libft.h"

int	ft_get_string_until_nl(t_gnl_data *data, char **line,
		unsigned long *line_size, int start)
{
	char	*temp_line;
	char	*temp_new;

	start = data->pos;
	while (data->pos < data->size - 1 && data->buff[data->pos] != '\n')
		data->pos += 1;
	temp_line = *line;
	temp_new = ft_gnl_substr(data->buff, start, data->pos - start + 1);
	if (temp_line == 0 && temp_new)
	{
		*line_size += data->pos - start + 1;
		*line = temp_new;
		return (1);
	}
	if (temp_new == 0 && temp_line)
	{
		free(temp_line);
		*line = 0;
		*line_size = 0;
		return (0);
	}
	*line = ft_gnl_strjoin(temp_line, temp_new, *line_size, data->pos - start
			+ 1);
	*line_size += data->pos - start + 1;
	return (ft_free_batch(1, 2, temp_line, temp_new));
}

char	*ft_gnl_read_loop(t_gnl_data *data, unsigned long *line_size)
{
	char	*line;

	line = 0;
	while (1)
	{
		if (data->pos == data->size)
		{
			data->pos = 0;
			data->size = read(data->fd, data->buff, BUFFER_SIZE);
			if (data->size <= 0)
				return (line);
		}
		if (ft_get_string_until_nl(data, &line, line_size, 0))
		{
			data->pos += 1;
			if (data->buff[data->pos - 1] == '\n')
				return (line);
		}
	}
}

/// fd -2 purges all the data
char	*get_next_line_real(int fd, unsigned long *line_size)
{
	static t_gnl_data	*data = 0;
	t_gnl_data			*dat;
	char				*ret;

	*line_size = 0;
	if (fd == -2)
	{
		ft_clear_all_gnl_data(&data);
		return (0);
	}
	dat = ft_get_gnl_data(fd, &data);
	if (!dat)
		return (0);
	ret = ft_gnl_read_loop(dat, line_size);
	if (!ret)
		ft_clear_gnl_fd(fd, &data);
	if (!ret)
		*line_size = 0;
	return (ret);
}

char	*get_next_line_count(int fd, unsigned long *size)
{
	return (get_next_line_real(fd, size));
}

char	*get_next_line(int fd)
{
	unsigned long	i;

	return (get_next_line_real(fd, &i));
}
