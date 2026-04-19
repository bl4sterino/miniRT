/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   array_process.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pberne <pberne@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/19 18:44:58 by pberne            #+#    #+#             */
/*   Updated: 2026/04/19 23:40:43 by pberne           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

t_io_res ft_parse_a(t_rbuf *rbuf, t_parsed_object *o)
{
	o->type = object_type_ambient_light;
	return (IO_RES_OK);
}

t_io_res	ft_parse_object(uint8_t *t, t_rbuf *rbuf, t_parsed_object *o)
{
	if (t[0] == 'A' && ft_isspace(t[1]))
		return (ft_parse_a(rbuf, o));
	else if (t[0] == 'C' && ft_isspace(t[1]))
		o->type = object_type_camera;
	else if (t[0] == 'L' && ft_isspace(t[1]))
		o->type = object_type_camera;
	else if (t[0] == 'p' && t[1] == 'l' && ft_isspace(t[2]))
		o->type = object_type_plane;
	else if (t[0] == 's' && t[1] == 'p' && ft_isspace(t[2]))
		o->type = object_type_sphere;
	else if (t[0] == 'c' && t[1] == 'y' && ft_isspace(t[2]))
		o->type = object_type_cylinder;
	else if (t[0] == 'q' && ft_isspace(t[1]))
		o->type = object_type_quad;
	else if (t[0] == 't' && ft_isspace(t[1]))
		o->type = object_type_triangle;
	else if (t[0] == 'e' && t[1] == 'l' && ft_isspace(t[2]))
		o->type = object_type_ellipsoid;
	else if (t[0] == 't' && t[1] == 'e' && t[2] == 'x' && ft_isspace(t[3]))
		o->type = object_type_texture_path;
	else if (t[0] == 's' && t[1] == 'k' && t[2] == 'y' && ft_isspace(t[3]))
		o->type = object_type_skybox;
	else if (t[0] == 'o' && t[1] == 'b' && t[2] == 'j' && ft_isspace(t[3]))
		o->type = object_type_wavefront;
}

t_io_res	ft_parse_line(t_rbuf *rbuf, t_parsed_object *o)
{
	t_io_res	r;
	uint8_t		t[4];
	size_t		i;

	i = 0;
	while (i < 4)
	{
		r = rbuf_read_byte(rbuf, &t[i]);
		if (r != IO_RES_OK || t[i] == 0 || t[i] == '\n')
			return (IO_RES_ERR);
		if (t[i] == ' ' || t[i] == '\t')
			break ;
		i++;
	}
	o->type = -1;
	ft_parse_object(t, rbuf, o);
	return (IO_RES_OK);
}

t_io_res	ft_rt_iter_next(t_rt_parser_iter *self, t_parsed_object *o)
{
	ft_parse_line(&self->rbuf, o);
	return (IO_RES_OK);
}