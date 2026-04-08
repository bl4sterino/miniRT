/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_mode.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pberne <pberne@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/08 15:38:33 by pberne            #+#    #+#             */
/*   Updated: 2026/04/08 15:41:59 by pberne           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

static inline void	ft_render_pixel_classic(t_data *d,
		t_thread_render_context *c, int render_mode, int eye)
{
	t_v3f	hit_color;

	hit_color = ft_get_pixel_color(c->ray, d->scene, &c->out,
			d->image.ray_targets[c->index]);
	if (render_mode == RENDER_DEFAULT)
		ft_add_pixel_to_accumulated_image(d, c->index, hit_color, eye);
	else if (render_mode == RENDER_NORMALS)
	{
		c->out.hit_normal = ft_v3f_add(ft_v3f_scale(c->out.hit_normal, 0.5f),
				(t_v3f){{0.5f, 0.5f, 0.5f}});
		ft_add_pixel_to_accumulated_image(d, c->index, c->out.hit_normal, eye);
	}
}

void	ft_render_mode_basic(t_data *d, t_thread_render_context *c, int cam_idx)
{
	c->target = ft_get_viewport_target(&c->vp, *c);
	c->ray = ft_setup_ray_target(c->ray, c->target, d->ray_bounces, 0);
	if (d->scene->cameras[cam_idx].render_mode != RENDER_BVH)
		ft_render_pixel_classic(d, c, d->scene->cameras[cam_idx].render_mode,
			0);
	else
		ft_add_pixel_to_accumulated_image(d, c->index,
			ft_shoot_ray_bvh_debug(c->ray, d->scene), 0);
}

void	ft_render_mode_stereo(t_data *d, t_thread_render_context *c,
		int cam_idx, t_ray ray)
{
	c->target = ft_get_viewport_target(&c->vp, *c);
	c->ray = ft_setup_ray_target(ray, c->target, d->ray_bounces, 0);
	c->ray.origin.v = ray.origin.v - c->cam.right.v * c->cam.stereo_space;
	if (d->scene->cameras[cam_idx].render_mode != RENDER_BVH)
		ft_render_pixel_classic(d, c, d->scene->cameras[cam_idx].render_mode,
			EYE_LEFT);
	else
		ft_add_pixel_to_accumulated_image(d, c->index,
			ft_shoot_ray_bvh_debug(c->ray, d->scene), EYE_LEFT);
	c->ray.origin.v = ray.origin.v + c->cam.right.v * c->cam.stereo_space;
	if (d->scene->cameras[cam_idx].render_mode != RENDER_BVH)
		ft_render_pixel_classic(d, c, d->scene->cameras[cam_idx].render_mode,
			EYE_RIGHT);
	else
		ft_add_pixel_to_accumulated_image(d, c->index,
			ft_shoot_ray_bvh_debug(c->ray, d->scene), EYE_RIGHT);
}
