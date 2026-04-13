/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_random.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pberne <pberne@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/19 13:33:40 by pberne            #+#    #+#             */
/*   Updated: 2026/03/04 17:37:59 by pberne           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_RANDOM_H
# define FT_RANDOM_H

# include <math.h>
# include <stdatomic.h>
# include <stdint.h>

static inline double	fast_rand_double(void)
{
	uint64_t						z;
	static _Thread_local uint64_t	state = 42;

	state += 0x9E3779B97F4A7C15ULL;
	z = state;
	z = (z ^ (z >> 30)) * 0xBF58476D1CE4E5B9ULL;
	z = (z ^ (z >> 27)) * 0x94D049BB133111EBULL;
	z = z ^ (z >> 31);
	return ((double)(z >> 11)*(1.0 / 9007199254740992.0));
}

static inline float	fast_rand(void)
{
	uint64_t						z;
	static _Thread_local uint64_t	state = 42;

	state += 0x9E3779B97F4A7C15ULL;
	z = state;
	z = (z ^ (z >> 30)) * 0xBF58476D1CE4E5B9ULL;
	z = (z ^ (z >> 27)) * 0x94D049BB133111EBULL;
	z = z ^ (z >> 31);
	return (((float)(z >> 40)*0.000000059604644775390625f));
}

#endif