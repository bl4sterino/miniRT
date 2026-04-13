/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   consume.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpotier <tpotier@learner.42.tech>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/18 19:38:48 by tpotier           #+#    #+#             */
/*   Updated: 2026/02/18 20:19:35 by tpotier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "io.h"

void	rbuf_consume(t_rbuf *self, size_t amt)
{
	self->start += amt;
	if (self->start > self->end)
		self->start = self->end;
}
