/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   array_parser.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pberne <pberne@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/18 08:36:39 by pberne            #+#    #+#             */
/*   Updated: 2026/04/19 23:33:20 by pberne           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"
#include <stdlib.h>
#include <sys/stat.h>


t_io_res	ft_add_parsed_object(t_rt_parser_iter *self, t_parsed_object *o)
{
	size_t new_cap;
	t_parsed_object *new;

	if (self->objects_len == self->objects_cap)
	{
		if (self->objects_cap == 0)
			new_cap = 16;
		else
			new_cap = self->objects_cap * 2;
		new = malloc(sizeof(*self->objects) * new_cap);
		if (new == NULL)
			return (IO_RES_ERR);
		ft_memcpy(new, self->objects, sizeof(*self->objects)
			* self->objects_len);
		free(self->objects);
		self->objects = new;
		self->objects_cap = new_cap;
	}
	self->objects[self->objects_len++] = *o;
	return (IO_RES_OK);
}

void	ft_rt_parser_iter_drop(t_rt_parser_iter *self)
{
	rbuf_drop(&self->rbuf);
	free(self->objects);
}

static void	ft_fatal_rt(char *p, int fd, t_rt_parser_iter *i)
{
	if (fd >= 0)
		close(fd);
	if (i)
		ft_rt_parser_iter_drop(i);
	ft_putstr_fd("Cannot load rt file: ", 2);
	ft_putstr_fd(p, 2);
	ft_exit_str_fd(1, "\n", 2);
}

t_io_res	rt_parser_iter_new(t_rt_parser_iter *self, int fd)
{
	self->objects_len = 0;
	self->objects_cap = 0;
	self->objects = NULL;
	return (rbuf_new(&self->rbuf, fd));
}

void	ft_array_parser(t_data *d, char *filepath)
{
	int					fd;
	t_rt_parser_iter	i;
	t_io_res r;
	t_parsed_object o;

	(void)d;
	fd = open(filepath, O_RDONLY);
	if (fd < 0)
		ft_fatal_rt(filepath, fd, NULL);

	r = rt_parser_iter_new(&i, fd);
	if (r != IO_RES_OK)
		ft_fatal_rt(filepath, fd, &i);
	
	while (1)
	{
		r = ft_rt_iter_next(&i, &o);
		if (r == IO_RES_EOF)
			break ;
		if (r != IO_RES_OK)
			ft_fatal_rt(filepath, fd, &i);
		ft_add_parsed_object(&i, &o);
	}
	ft_rt_parser_iter_drop(&i);
	close(fd);
}


