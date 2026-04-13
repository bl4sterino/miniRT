/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   v3d_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pberne <pberne@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/24 18:08:29 by pberne            #+#    #+#             */
/*   Updated: 2026/03/06 14:30:16 by pberne           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_v3d	ft_v3d_div_safe(t_v3d v1, t_v3d v2)
{
	t_v3d	v;

	v.x = v1.x / copysign(fmax(fabs(v2.x), EPSILON), v2.x);
	v.y = v1.y / copysign(fmax(fabs(v2.y), EPSILON), v2.y);
	v.z = v1.z / copysign(fmax(fabs(v2.z), EPSILON), v2.z);
	return (v);
}
