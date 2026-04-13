/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mem.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpotier <tpotier@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/30 19:20:26 by tpotier           #+#    #+#             */
/*   Updated: 2026/04/01 15:01:26 by tpotier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MEM_H
# define MEM_H

# include <stddef.h>

void	mem_cpy(void *dst, void *src, size_t amt);
size_t	mem_strlen(const char *s);

#endif
