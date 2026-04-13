/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_read_file_gc.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pberne <pberne@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/22 22:32:46 by pberne            #+#    #+#             */
/*   Updated: 2026/03/04 17:33:32 by pberne           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_read_loop(t_read_file_context *c, char *buffer)
{
	c->just_read = read(c->fd, buffer, 4096);
	if (c->just_read < 0)
		return (0);
	while (c->just_read)
	{
		c->filesize += c->just_read;
		c->just_read = read(c->fd, c->buffer, 4096);
	}
	return (buffer);
}

char	*ft_read_file_gc_id(char *filepath, int malloc_id)
{
	t_read_file_context	c;

	c.fd = open(filepath, O_RDONLY);
	if (c.fd < 0)
		return (0);
	c.filesize = 0;
	c.just_read = 0;
	if (!ft_read_loop(&c, c.buffer))
		return (0);
	close(c.fd);
	c.out = ft_malloc_id(c.filesize + 1, malloc_id);
	c.fd = open(filepath, O_RDONLY);
	if (c.fd < 0)
		return (0);
	c.filesize = 0;
	if (!ft_read_loop(&c, c.out))
	{
		ft_free(c.out);
		return (0);
	}
	c.out[c.filesize] = '\0';
	return (c.out);
}
