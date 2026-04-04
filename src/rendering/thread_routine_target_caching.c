/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread_routine_target_caching.c                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pberne <pberne@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/02 17:08:05 by pberne            #+#    #+#             */
/*   Updated: 2026/04/04 20:59:33 by pberne           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

static inline int	ft_cache_ray_target_2(t_data *d, t_thread_render_context *c,
		int hit_comp)
{
	t_v3f	target;
	int		hit;

	hit = SELECTED_NONE;
	target.v = d->viewport.raw_top_left.v + (d->viewport.x_delta.v
			* (float)c->pixel.x + d->viewport.y_delta.v * (float)(c->pixel.y
				+ 1));
	c->ray = ft_setup_ray_target(c->ray, target, 0, 0);
	ft_shoot_ray(c->ray, d->scene, &hit);
	if (hit != hit_comp)
		return (SELECTED_NONE);
	hit = SELECTED_NONE;
	target.v = d->viewport.raw_top_left.v + (d->viewport.x_delta.v
			* (float)(c->pixel.x + 1) + d->viewport.y_delta.v
			* (float)(c->pixel.y + 1));
	c->ray = ft_setup_ray_target(c->ray, target, 0, 0);
	ft_shoot_ray(c->ray, d->scene, &hit);
	if (hit != hit_comp)
		return (SELECTED_NONE);
	else if (hit == SELECTED_NONE)
		return (SELECTED_SKYBOX);
	return (hit);
}

// Check all corners and cache an id if the ray can only hit one object
// Returns the object or SELECTED_SKYBOX if teh ray always end up hitting the
// same thing
// Returns SELECTED_NONE if the ray can intersect multiple objects.
// TODO maybe try to cache the multiple objects, as iterating through those may
// be faster
int	ft_cache_ray_target(t_data *d, t_thread_render_context *c)
{
	t_v3f	target;
	int		hit_comp;
	int		hit;

	hit = SELECTED_NONE;
	target.v = d->viewport.raw_top_left.v + (d->viewport.x_delta.v
			* (float)c->pixel.x + d->viewport.y_delta.v * (float)c->pixel.y);
	c->ray = ft_setup_ray_target(c->ray, target, 0, 0);
	ft_shoot_ray(c->ray, d->scene, &hit);
	hit_comp = hit;
	hit = SELECTED_NONE;
	target.v = d->viewport.raw_top_left.v + (d->viewport.x_delta.v
			* (float)(c->pixel.x + 1) + d->viewport.y_delta.v
			* (float)c->pixel.y);
	c->ray = ft_setup_ray_target(c->ray, target, 0, 0);
	ft_shoot_ray(c->ray, d->scene, &hit);
	if (hit != hit_comp)
		return (SELECTED_NONE);
	return (ft_cache_ray_target_2(d, c, hit_comp));
}
