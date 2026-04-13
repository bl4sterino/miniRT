/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cpy.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpotier <tpotier@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/30 19:19:07 by tpotier           #+#    #+#             */
/*   Updated: 2026/04/01 15:01:35 by tpotier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdint.h>

#include "mem.h"

void	mem_cpy(void *dst, void *src, size_t amt)
{
	size_t	i;

	i = 0;
	while (i < amt)
	{
		((uint8_t *)dst)[i] = ((uint8_t *)src)[i];
		i++;
	}
}
