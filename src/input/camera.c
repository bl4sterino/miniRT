/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pberne <pberne@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/02 19:37:39 by pberne            #+#    #+#             */
/*   Updated: 2026/04/06 19:46:05 by tpotier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

// Handles camera collision
int	ft_try_move(t_data *d, t_camera *cam, t_v3f *movement)
{
	t_ray	ray;
	int		hit;
	float	ray_len;
	t_v3f	hit_normal;

	if (ft_v3f_length(*movement) < COL_EPSILON)
		return (0);
	if (cam->noclip)
		return (1);
	ray.origin = cam->position;
	ray = ft_setup_ray_direction(ray, ft_v3f_normalize(*movement), 0, 0);
	ray_len = ft_shoot_ray(ray, d->scene, &hit);
	if (ray_len < COL_EPSILON)
		return (0);
	if (ray_len - COL_EPSILON < ft_v3f_length(*movement))
	{
		hit_normal = ft_get_hit_normal(ft_ray_at(ray, ray_len - COL_EPSILON),
			d->scene, hit, ft_v3f_normalize(*movement));
		movement->v -= ft_v3f_dot(*movement, hit_normal) * hit_normal.v;
		return (ft_try_move(d, cam, movement));
	}
	return (1);
}

void	ft_camera_move(t_data *d)
{
	t_camera_move_context	c;
	t_camera	*cam;

	cam = get_active_camera(d->scene);
	if (ft_get_key_down(XK_b, d))
		cam->noclip = !cam->noclip;
	c.campos = cam->position;
	c.camdir = cam->direction;
	c.movement.x = ft_get_key(XK_d, d) - ft_get_key(XK_a, d);
	c.movement.z = ft_get_key(XK_w, d) - ft_get_key(XK_s, d);
	c.movement.y = ft_get_key(XK_space, d) - ft_get_key(XK_Control_L, d);
	c.movement.v *= (float)d->deltatime * CAM_MOVEMENT_SPEED * (1.0f + CAM_BOOST
			* (float)ft_get_key(XK_Shift_L, d));
	c.yaw = atan2f(c.camdir.x, c.camdir.z);
	c.campos.x += sinf(c.yaw) * c.movement.z;
	c.campos.z += cosf(c.yaw) * c.movement.z;
	c.campos.x += cosf(c.yaw) * c.movement.x;
	c.campos.z += -sinf(c.yaw) * c.movement.x;
	c.campos.y += c.movement.y;
	c.movement.v = c.campos.v - cam->position.v;
	if (ft_try_move(d, cam, &c.movement))
	{
		d->dirty_frame = 1;
		cam->position.v += c.movement.v;
	}
}

void	ft_camera_rotate(t_data *d)
{
	t_v3f		cam_rot;
	float		rotx;
	float		roty;
	float		key_rot;
	t_camera	*cam;

	cam = get_active_camera(d->scene);
	cam_rot = ft_cam_v3f_to_euler(cam->direction);
	rotx = d->input.mouse_delta.y * CAM_ROTATION_SPEED * (cam->fov / 85.0f);
	key_rot = (float)-ft_get_key(XK_i, d) + (float)ft_get_key(XK_k, d);
	rotx += key_rot * d->deltatime * CAM_ROTATION_SPEED_KEY;
	roty = d->input.mouse_delta.x * CAM_ROTATION_SPEED * (cam->fov / 85.0);
	key_rot = (float)-ft_get_key(XK_j, d) + (float)ft_get_key(XK_l, d);
	roty += key_rot * d->deltatime * CAM_ROTATION_SPEED_KEY;
	cam_rot.x = ft_clampd(cam_rot.x + rotx, -85.0, 85.0);
	cam_rot.y = cam_rot.y + roty;
	while (cam_rot.y < -180.0)
		cam_rot.y += 360.0;
	while (cam_rot.y > 180.0)
		cam_rot.y -= 360.0;
	cam->direction = ft_cam_euler_to_v3f(cam_rot);
	if (fabs(rotx) > EPSILON || fabs(roty) > EPSILON)
		d->dirty_frame = 1;
}

void	ft_camera_zoom(t_data *d)
{
	t_camera	*cam;

	cam = get_active_camera(d->scene);
	if (ft_get_key_down(MOUSE_SCROLL_DOWN, d))
	{
		cam->fov *= 1.05f;
		d->dirty_frame = 1;
	}
	if (ft_get_key_down(MOUSE_SCROLL_UP, d))
	{
		cam->fov *= 0.95f;
		d->dirty_frame = 1;
	}
}
