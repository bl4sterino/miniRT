/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_get_bounds_2.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pberne <pberne@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/09 14:17:35 by pberne            #+#    #+#             */
/*   Updated: 2026/03/09 14:17:43 by pberne           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

t_bounds	ft_get_ellipsoid_bounds(t_ellipsoid el)
{
	t_bounds	bounds;

	bounds.min = ft_v3f_sub(el.position, el.radii);
	bounds.max = ft_v3f_add(el.position, el.radii);
	return (bounds);
}
