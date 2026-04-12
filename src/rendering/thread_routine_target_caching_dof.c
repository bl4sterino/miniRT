/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread_routine_target_caching_dof.c                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pberne <pberne@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/02 17:08:05 by pberne            #+#    #+#             */
/*   Updated: 2026/04/12 18:16:05 by pberne           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

static inline int	ft_cache_ray_target_dof_4(t_data *d, t_viewport *vp,
		t_thread_render_context *c, int hit_comp)
{
	t_v3f	target;
	int		hit;

	hit = SELECTED_NONE;
	target.v = vp->raw_top_left.v + (vp->x_delta.v * (float)(c->pixel.x + 1)
			+ vp->y_delta.v * (float)(c->pixel.y + 1));
	c->ray.origin = ft_get_camera_origin_dof_cache_limit(&c->cam, v3f(-1.0f,
				1.0f, 0.0f));
	c->ray = ft_setup_ray_target(c->ray, target, 0, 0);
	ft_shoot_ray(c->ray, d->scene, &hit);
	if (hit != hit_comp)
		return (SELECTED_NONE);
	hit = SELECTED_NONE;
	target.v = vp->raw_top_left.v + (vp->x_delta.v * (float)(c->pixel.x + 1)
			+ vp->y_delta.v * (float)(c->pixel.y + 1));
	c->ray.origin = ft_get_camera_origin_dof_cache_limit(&c->cam, v3f(1.0f,
				-1.0f, 0.0f));
	c->ray = ft_setup_ray_target(c->ray, target, 0, 0);
	ft_shoot_ray(c->ray, d->scene, &hit);
	if (hit != hit_comp)
		return (SELECTED_NONE);
	else if (hit == SELECTED_NONE)
		return (SELECTED_SKYBOX);
	return (hit);
}

static inline int	ft_cache_ray_target_dof_3(t_data *d, t_viewport *vp,
		t_thread_render_context *c, int hit_comp)
{
	t_v3f	target;
	int		hit;

	hit = SELECTED_NONE;
	target.v = vp->raw_top_left.v + (vp->x_delta.v * (float)c->pixel.x
			+ vp->y_delta.v * (float)(c->pixel.y + 1));
	c->ray.origin = ft_get_camera_origin_dof_cache_limit(&c->cam, v3f(1.0f,
				1.0f, 0.0f));
	c->ray = ft_setup_ray_target(c->ray, target, 0, 0);
	ft_shoot_ray(c->ray, d->scene, &hit);
	if (hit != hit_comp)
		return (SELECTED_NONE);
	c->ray.origin = ft_get_camera_origin_dof_cache_limit(&c->cam, v3f(-1.0f,
				-1.0f, 0.0f));
	c->ray = ft_setup_ray_target(c->ray, target, 0, 0);
	ft_shoot_ray(c->ray, d->scene, &hit);
	if (hit != hit_comp)
		return (SELECTED_NONE);
	return (ft_cache_ray_target_dof_4(d, vp, c, hit_comp));
}

static inline int	ft_cache_ray_target_dof_2(t_data *d, t_viewport *vp,
		t_thread_render_context *c, int hit_comp)
{
	t_v3f	target;
	int		hit;

	hit = SELECTED_NONE;
	target.v = vp->raw_top_left.v + (vp->x_delta.v * (float)(c->pixel.x + 1)
			+ vp->y_delta.v * (float)c->pixel.y);
	c->ray.origin = ft_get_camera_origin_dof_cache_limit(&c->cam, v3f(-1.0f,
				-1.0f, 0.0f));
	c->ray = ft_setup_ray_target(c->ray, target, 0, 0);
	ft_shoot_ray(c->ray, d->scene, &hit);
	if (hit != hit_comp)
		return (SELECTED_NONE);
	hit = SELECTED_NONE;
	c->ray.origin = ft_get_camera_origin_dof_cache_limit(&c->cam, v3f(1.0f,
				1.0f, 0.0f));
	c->ray = ft_setup_ray_target(c->ray, target, 0, 0);
	ft_shoot_ray(c->ray, d->scene, &hit);
	if (hit != hit_comp)
		return (SELECTED_NONE);
	return (ft_cache_ray_target_dof_3(d, vp, c, hit_comp));
}

int	ft_cache_ray_target_dof(t_data *d, t_viewport *vp,
		t_thread_render_context *c)
{
	t_v3f	target;
	int		hit_comp;
	int		hit;

	hit = SELECTED_NONE;
	target.v = vp->raw_top_left.v + (vp->x_delta.v * (float)c->pixel.x
			+ vp->y_delta.v * (float)c->pixel.y);
	c->ray.origin = ft_get_camera_origin_dof_cache_limit(&c->cam, v3f(1.0f,
				-1.0f, 0.0f));
	c->ray = ft_setup_ray_target(c->ray, target, 0, 0);
	ft_shoot_ray(c->ray, d->scene, &hit);
	hit_comp = hit;
	hit = SELECTED_NONE;
	c->ray.origin = ft_get_camera_origin_dof_cache_limit(&c->cam, v3f(1.0f,
				1.0f, 0.0f));
	c->ray = ft_setup_ray_target(c->ray, target, 0, 0);
	ft_shoot_ray(c->ray, d->scene, &hit);
	if (hit != hit_comp)
		return (SELECTED_NONE);
	return (ft_cache_ray_target_dof_2(d, vp, c, hit_comp));
}
