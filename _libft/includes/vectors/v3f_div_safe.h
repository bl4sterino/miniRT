/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   v3f_div_safe.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pberne <pberne@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/06 14:28:28 by pberne            #+#    #+#             */
/*   Updated: 2026/04/12 12:13:18 by pberne           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef V3F_DIV_SAFE_H
# define V3F_DIV_SAFE_H

# include "vectors.h"

static inline t_v3f	ft_v3f_div_safe(t_v3f v1, t_v3f v2)
{
	t_v4si	abs_mask;
	t_v4si	sign_mask;
	t_v4sf	abs;
	t_v4si	sign;
	t_v4sf	divider;

	abs_mask = (t_v4si){0x7FFFFFFF, 0x7FFFFFFF, 0x7FFFFFFF, 0x7FFFFFFF};
	sign_mask = (t_v4si){(int)0x80000000, (int)0x80000000, (int)0x80000000,
		(int)0x80000000};
	abs = (t_v4sf)(abs_mask & (t_v4si)v2.v);
	sign = sign_mask & (t_v4si)v2.v;
	divider = ft_v3f_max((t_v3f){{abs[0], abs[1], abs[2], abs[3]}},
			v3f_a(0.0001f)).v;
	divider = (t_v4sf)((t_v4si)divider | sign);
	return ((t_v3f){.v = v1.v / divider});
}

#endif
