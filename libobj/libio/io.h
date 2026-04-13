/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   io.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpotier <tpotier@learner.42.tech>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/18 19:42:53 by tpotier           #+#    #+#             */
/*   Updated: 2026/02/18 21:04:40 by tpotier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef IO_H
# define IO_H

# include <stdint.h>
# include <stddef.h>

typedef enum e_io_res
{
	IO_RES_OK = 0,
	IO_RES_ERR = -1,
	IO_RES_EOF = 1,
}	t_io_res;

/*
 * A bufferized reader.
 *
 * The buffer can grow in order to contain a full token.
 */
typedef struct s_rbuf
{
	int		fd;
	uint8_t	*buf;
	size_t	cap;
	size_t	start;
	size_t	end;
}	t_rbuf;

/*
 * Initializes a bufferized reader.
 */
void		rbuf_init(t_rbuf *self);

/*
 * Create a new bufferized reader with the default capacity.
 *
 * Returns `RES_OK` on success, `RES_ERR` if the allocation failed.
 */
t_io_res	rbuf_new(t_rbuf *self, int fd)
			__attribute__ ((warn_unused_result));

t_io_res	rbuf_peek_byte(t_rbuf *self, uint8_t *b)
			__attribute__ ((warn_unused_result));
t_io_res	rbuf_read_byte(t_rbuf *self, uint8_t *b)
			__attribute__ ((warn_unused_result));

/*
 * Comsumes `amt` bytes from the reader.
 *
 * Behavior is undefined is `amt` is greater than current buffer length.
 */
void		rbuf_consume(t_rbuf *self, size_t amt);

/*
 * Releases ressources allocated to the reader.
 */
void		rbuf_drop(t_rbuf *self);

#endif
