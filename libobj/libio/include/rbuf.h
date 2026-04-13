/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rbuf.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpotier <tpotier@learner.42.tech>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/18 16:52:51 by tpotier           #+#    #+#             */
/*   Updated: 2026/02/18 20:14:50 by tpotier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RBUF_H
# define RBUF_H

# include "io.h"

# define DEFAULT_CAPACITY	4096

/*
 * Fills the buffer if it is empty by reading from the file descriptor.
 *
 * Returns `RES_OK` on success, `RES_ERR` if a read error occured and `RES_EOF`
 * if there is nothing left to read.
 */
t_io_res	rbuf_fill(t_rbuf *self);

#endif
