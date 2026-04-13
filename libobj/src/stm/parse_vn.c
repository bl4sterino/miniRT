/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_vn.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpotier <tpotier@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/10 16:21:20 by tpotier           #+#    #+#             */
/*   Updated: 2026/04/10 16:21:58 by tpotier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "stm.h"

t_io_res	obj_stm_parse_vn(t_obj_vn *self, t_rbuf *rbuf)
{
	t_io_res	r;

	r = obj_skip_ws(rbuf);
	if (r != IO_RES_OK)
		return (IO_RES_ERR);
	r = obj_parse_float(&self->i, rbuf);
	if (r != IO_RES_OK)
		return (IO_RES_ERR);
	r = obj_skip_ws(rbuf);
	if (r != IO_RES_OK)
		return (IO_RES_ERR);
	r = obj_parse_float(&self->j, rbuf);
	if (r != IO_RES_OK)
		return (IO_RES_ERR);
	r = obj_skip_ws(rbuf);
	if (r != IO_RES_OK)
		return (IO_RES_ERR);
	r = obj_parse_float(&self->k, rbuf);
	if (r != IO_RES_OK)
		return (IO_RES_ERR);
	return (IO_RES_OK);
}
