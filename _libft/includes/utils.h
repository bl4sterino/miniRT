/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pberne <pberne@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/22 14:45:02 by pberne            #+#    #+#             */
/*   Updated: 2026/03/02 19:25:23 by pberne           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_H
# define UTILS_H

# include "libft.h"

int						*ft_malloc_int(int n);
int						*ft_malloc_id_int(int n, int malloc_id);

static inline double	tn_d(int cond, double out1, double out2)
{
	if (cond)
		return (out1);
	return (out2);
}

static inline float	tn_f(int cond, float out1, float out2)
{
	if (cond)
		return (out1);
	return (out2);
}

static inline double	tn_i(int cond, int out1, int out2)
{
	if (cond)
		return (out1);
	return (out2);
}

#endif