/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpotier <tpotier@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/09 22:50:39 by tpotier           #+#    #+#             */
/*   Updated: 2026/04/10 19:19:43 by tpotier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "stm.h"

static t_io_res	parse_ty(t_stmty *ty, t_rbuf *rbuf)
{
	t_io_res	r;
	uint8_t		t[3];
	size_t		i;

	i = 0;
	while (i < 3)
	{
		r = rbuf_read_byte(rbuf, &t[i]);
		if (r != IO_RES_OK)
			return (IO_RES_ERR);
		if (t[i] == ' ' || t[i] == '\t')
			break ;
		i++;
	}
	*ty = STM_UNKNOWN;
	if (t[0] == 'v' && (t[1] == ' ' || t[1] == '\t'))
		*ty = STM_V;
	else if (t[0] == 'v' && t[1] == 'n' && (t[2] == ' ' || t[2] == '\t'))
		*ty = STM_VN;
	else if (t[0] == 'v' && t[1] == 't' && (t[2] == ' ' || t[2] == '\t'))
		*ty = STM_VT;
	else if (t[0] == 'f' && (t[1] == ' ' || t[1] == '\t'))
		*ty = STM_F;
	return (IO_RES_OK);
}

static t_io_res	obj_stm_parse_one(t_stm *self, t_rbuf *rbuf)
{
	t_io_res	r;

	r = parse_ty(&self->ty, rbuf);
	if (r != IO_RES_OK)
		return (r);
	if (self->ty == STM_V)
		r = obj_stm_parse_v(&self->as.v, rbuf);
	else if (self->ty == STM_VN)
		r = obj_stm_parse_vn(&self->as.vn, rbuf);
	else if (self->ty == STM_VT)
		r = obj_stm_parse_vt(&self->as.vt, rbuf);
	else if (self->ty == STM_F)
		r = obj_stm_parse_f(&self->as.f, rbuf);
	if (r != IO_RES_OK)
		return (r);
	return (obj_skip_to_nl(rbuf));
}

t_io_res	obj_stm_parse(t_stm *self, t_rbuf *rbuf)
{
	t_io_res	r;
	uint8_t		b;

	while (1)
	{
		r = rbuf_peek_byte(rbuf, &b);
		if (r != IO_RES_OK)
			return (r);
		if (b != ' ' && b != '\t' && b != '\r' && b != '\n' && b != '#')
			break ;
		r = obj_skip_ws_comment(rbuf);
		if (r != IO_RES_OK)
			return (r);
		r = rbuf_read_byte(rbuf, &b);
		if (r != IO_RES_OK)
			return (r);
		if (b != '\n')
			return (IO_RES_ERR);
	}
	return (obj_stm_parse_one(self, rbuf));
}
