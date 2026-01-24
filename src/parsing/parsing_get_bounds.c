/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_get_bounds.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pberne <pberne@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/24 17:09:03 by pberne            #+#    #+#             */
/*   Updated: 2026/01/24 17:11:26 by pberne           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

t_bounds	ft_get_sphere_bounds(t_sphere sphere)
{
	t_v3d		v_radius;
	t_bounds	bounds;

	v_radius = (t_v3d){sphere.radius, sphere.radius, sphere.radius};
	bounds.min = ft_v3d_sub(sphere.position, v_radius);
	bounds.max = ft_v3d_add(sphere.position, v_radius);
	return (bounds);
}
