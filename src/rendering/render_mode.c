/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_mode.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pberne <pberne@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/08 15:38:33 by pberne            #+#    #+#             */
/*   Updated: 2026/04/12 18:15:53 by pberne           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

t_v3f	ft_get_color_from_ray_targets(t_data *d, t_thread_render_context *c)
{
	int	target;

	target = d->image.ray_targets[c->index];
	if (target < 0)
		target = -(target + 1);
	if (target == SELECTED_NONE)
		return (v3f(0.0f, 0.0f, 0.0f));
	else if (target == SELECTED_SKYBOX)
		return (v3f(129.0f / 255.0f, 179.0f / 255.0f, 240.0f / 255.0f));
	return (d->image.targets_colors[target % 1024]);
}

void	ft_render_special_mode(t_data *d, int render_mode,
		t_thread_render_context *c, int eye)
{
	if (render_mode == RENDER_BVH)
		ft_add_pixel_to_accumulated_image(d, c, ft_shoot_ray_bvh_debug(c->ray,
				d->scene), eye);
	else if (render_mode == RENDER_RAY_TARGETS)
		ft_add_pixel_to_accumulated_image(d, c, ft_get_color_from_ray_targets(d,
				c), eye);
}

static inline void	ft_render_pixel_classic(t_data *d,
		t_thread_render_context *c, int render_mode, int eye)
{
	t_v3f	hit_color;

	hit_color = ft_get_pixel_color(c->ray, d->scene, &c->out,
			d->image.ray_targets[c->index]);
	if (render_mode == RENDER_DEFAULT)
		ft_add_pixel_to_accumulated_image(d, c, hit_color, eye);
	else if (render_mode == RENDER_NORMALS)
	{
		c->out.hit_normal = ft_v3f_add(ft_v3f_scale(c->out.hit_normal, 0.5f),
				(t_v3f){{0.5f, 0.5f, 0.5f}});
		ft_add_pixel_to_accumulated_image(d, c, c->out.hit_normal, eye);
	}
}

void	ft_render_mode_basic(t_data *d, t_thread_render_context *c, int cam_idx)
{
	c->target = ft_get_viewport_target(&c->vp, c->pixel);
	c->ray.origin = ft_get_camera_origin_dof(&c->cam);
	c->ray = ft_setup_ray_target(c->ray, c->target, d->ray_bounces, 0);
	if (d->scene->cameras[cam_idx].render_mode < RENDER_BVH)
		ft_render_pixel_classic(d, c, d->scene->cameras[cam_idx].render_mode,
			0);
	else
		ft_render_special_mode(d, d->scene->cameras[cam_idx].render_mode, c, 0);
}

void	ft_render_mode_stereo(t_data *d, t_thread_render_context *c,
		int cam_idx)
{
	t_v2i	pixel;

	pixel.y = c->pixel.y;
	pixel.x = c->pixel.x + (int)c->cam.stereo_offset;
	c->target = ft_get_viewport_target(&c->vp, pixel);
	c->ray.origin = ft_get_camera_origin_dof(&c->cam);
	c->ray = ft_setup_ray_target(c->ray, c->target, d->ray_bounces, 0);
	c->ray.origin.v = c->cam.position.v - c->cam.right.v * c->cam.stereo_space;
	if (d->scene->cameras[cam_idx].render_mode != RENDER_BVH)
		ft_render_pixel_classic(d, c, d->scene->cameras[cam_idx].render_mode,
			EYE_LEFT);
	else
		ft_render_special_mode(d, d->scene->cameras[cam_idx].render_mode, c,
			EYE_LEFT);
	pixel.x = c->pixel.x - (int)c->cam.stereo_offset;
	c->target = ft_get_viewport_target(&c->vp, pixel);
	c->ray.origin = ft_get_camera_origin_dof(&c->cam);
	c->ray = ft_setup_ray_target(c->ray, c->target, d->ray_bounces, 0);
	c->ray.origin.v = c->cam.position.v + c->cam.right.v * c->cam.stereo_space;
	if (d->scene->cameras[cam_idx].render_mode != RENDER_BVH)
		ft_render_pixel_classic(d, c, d->scene->cameras[cam_idx].render_mode,
			EYE_RIGHT);
	else
		ft_render_special_mode(d, d->scene->cameras[cam_idx].render_mode, c,
			EYE_RIGHT);
}
