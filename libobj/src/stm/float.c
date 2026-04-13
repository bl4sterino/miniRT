/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   float.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpotier <tpotier@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/10 15:42:25 by tpotier           #+#    #+#             */
/*   Updated: 2026/04/10 16:18:54 by tpotier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "stm.h"

static double	float_compute(t_stm_float f)
{
	double	d;

	d = f.frac_part;
	while (f.frac_digits > 0)
	{
		d /= 10;
		f.frac_digits--;
	}
	d += f.int_part;
	if (f.is_neg)
		d *= -1;
	return (d);
}

static t_io_res	parse_int_part(t_stm_float *f, t_rbuf *rbuf)
{
	t_io_res	r;
	uint8_t		b;

	r = rbuf_peek_byte(rbuf, &b);
	if (r != IO_RES_OK)
		return (IO_RES_ERR);
	if (b == '-')
		rbuf_consume(rbuf, 1);
	f->is_neg = b == '-';
	f->int_part = 0;
	while (1)
	{
		r = rbuf_read_byte(rbuf, &b);
		if (r != IO_RES_OK)
			return (IO_RES_ERR);
		if (b == '.')
			break ;
		if (!('0' <= b && b <= '9'))
			return (IO_RES_ERR);
		f->int_part = f->int_part * 10 + b - '0';
	}
	return (IO_RES_OK);
}

static t_io_res	parse_frac_part(t_stm_float *f, t_rbuf *rbuf)
{
	t_io_res	r;
	uint8_t		b;

	f->frac_part = 0;
	f->frac_digits = 0;
	while (1)
	{
		r = rbuf_peek_byte(rbuf, &b);
		if (r != IO_RES_OK)
			return (r);
		if (!('0' <= b && b <= '9'))
			break ;
		f->frac_part = f->frac_part * 10 + b - '0';
		f->frac_digits++;
		rbuf_consume(rbuf, 1);
	}
	return (IO_RES_OK);
}

t_io_res	obj_parse_float(double *self, t_rbuf *rbuf)
{
	t_stm_float	f;
	t_io_res	r;

	r = parse_int_part(&f, rbuf);
	if (r != IO_RES_OK)
		return (r);
	r = parse_frac_part(&f, rbuf);
	if (r != IO_RES_OK)
		return (r);
	*self = float_compute(f);
	return (IO_RES_OK);
}
