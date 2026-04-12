/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread_routine_target_caching.c                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pberne <pberne@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/02 17:08:05 by pberne            #+#    #+#             */
/*   Updated: 2026/04/12 18:12:39 by pberne           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

static inline int	ft_cache_ray_target_2(t_data *d, t_viewport *vp,
		t_thread_render_context *c, int hit_comp)
{
	t_v3f	target;
	int		hit;

	hit = SELECTED_NONE;
	target.v = vp->raw_top_left.v + (vp->x_delta.v * (float)c->pixel.x
			+ vp->y_delta.v * (float)(c->pixel.y + 1));
	c->ray = ft_setup_ray_target(c->ray, target, 0, 0);
	ft_shoot_ray(c->ray, d->scene, &hit);
	if (hit != hit_comp)
		return (SELECTED_NONE);
	hit = SELECTED_NONE;
	target.v = vp->raw_top_left.v + (vp->x_delta.v * (float)(c->pixel.x + 1)
			+ vp->y_delta.v * (float)(c->pixel.y + 1));
	c->ray = ft_setup_ray_target(c->ray, target, 0, 0);
	ft_shoot_ray(c->ray, d->scene, &hit);
	if (hit != hit_comp)
		return (SELECTED_NONE);
	else if (hit == SELECTED_NONE)
		return (SELECTED_SKYBOX);
	return (hit);
}

int	ft_cache_ray_target(t_data *d, t_viewport *vp, t_thread_render_context *c)
{
	t_v3f	target;
	int		hit_comp;
	int		hit;

	hit = SELECTED_NONE;
	target.v = vp->raw_top_left.v + (vp->x_delta.v * (float)c->pixel.x
			+ vp->y_delta.v * (float)c->pixel.y);
	c->ray = ft_setup_ray_target(c->ray, target, 0, 0);
	ft_shoot_ray(c->ray, d->scene, &hit);
	hit_comp = hit;
	hit = SELECTED_NONE;
	target.v = vp->raw_top_left.v + (vp->x_delta.v * (float)(c->pixel.x + 1)
			+ vp->y_delta.v * (float)c->pixel.y);
	c->ray = ft_setup_ray_target(c->ray, target, 0, 0);
	ft_shoot_ray(c->ray, d->scene, &hit);
	if (hit != hit_comp)
		return (SELECTED_NONE);
	return (ft_cache_ray_target_2(d, vp, c, hit_comp));
}
