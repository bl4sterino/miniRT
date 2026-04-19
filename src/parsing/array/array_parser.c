/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   array_parser.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pberne <pberne@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/18 08:36:39 by pberne            #+#    #+#             */
/*   Updated: 2026/04/19 18:43:57 by pberne           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"
#include <stdlib.h>
#include <sys/stat.h>


int	ft_fetch_rt_data(t_rt_parser_data *data, int fd)
{
	struct stat	statbuf;
	size_t		total_read;
	ssize_t		just_read;

	ft_bzero(data, sizeof(t_rt_parser_data));
	fstat(fd, &statbuf);
	data->buffer_size = statbuf.st_size;
	data->buffer = ft_malloc_id(data->buffer_size, malloc_id_parsing);
	total_read = 0;
	just_read = read(fd, data->buffer + total_read, data->buffer_size
			- total_read);
	while (just_read > 0 && total_read + just_read < data->buffer_size)
	{
		total_read += just_read;
		just_read = read(fd, data->buffer + total_read, data->buffer_size
				- total_read);
	}
	if (just_read < 0)
		ft_exit(1);
	ft_process_data(data);
	return (0);
}

void	ft_add_object(t_rt_parser_data *data, t_parsed_object object)
{
	size_t new_cap;
	char **new;

	if (data->objects_len == data->objects_cap)
	{
		if (data->objects_cap == 0)
			new_cap = 16;
		else
			new_cap *= 2;
		new = malloc(sizeof(char *) * new_cap);
		if (new == NULL)
			return (-1);
		ft_memcpy(new, data->objects, sizeof(*data->objects)
			* data->objects_len);
		free(data->objects);
		data->objects = new;
		data->objects_cap = new_cap;
	}
	data->objects[data->objects_len++] = object;
}

t_parsed_object	*ft_array_parser(t_data *d, char *filepath)
{
	int					fd;
	t_rt_parser_data	data;

	(void)d;
	fd = open(filepath, O_RDONLY);
	if (fd == -1)
		ft_exit_str_fd(EXIT_FAILURE, "Failed to open map\n", 2);
	ft_add_exit(ft_malloc_int(fd), ft_exit_close_fd);
	if (ft_fetch_rt_data(&data, fd) < 0)
	{
		free(data.buffer);
		free(data.objects);
	}
	ft_process_data(&data);
	return (0);
}


