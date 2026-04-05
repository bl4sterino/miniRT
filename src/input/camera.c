/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pberne <pberne@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/02 19:37:39 by pberne            #+#    #+#             */
/*   Updated: 2026/04/05 22:17:30 by pberne           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

int		ft_try_move(t_data *d, t_v3f *movement);

int	ft_subtract_illegal_direction(t_data *d, t_v3f *movement, int hit,
		t_v3f hit_point)
{
	t_v3f	hit_normal;

	hit_normal = ft_get_hit_normal(hit_point, d->scene, hit,
			ft_v3f_normalize(*movement));
	movement->v = movement->v - ft_v3f_dot(*movement, hit_normal)
		* hit_normal.v;
	return (ft_try_move(d, movement));
}

// Handles camera collision
int	ft_try_move(t_data *d, t_v3f *movement)
{
	t_ray	ray;
	int		out;
	float	ray_len;

	if (ft_v3f_length(*movement) < COL_EPSILON)
		return (0);
	if (d->scene->camera.noclip)
		return (1);
	ray.origin = d->scene->camera.position;
	ray = ft_setup_ray_direction(ray, ft_v3f_normalize(*movement), 0, 0);
	ray_len = ft_shoot_ray(ray, d->scene, &out);
	if (ray_len < COL_EPSILON)
		return (0);
	if (ray_len - COL_EPSILON < ft_v3f_length(*movement))
		return (ft_subtract_illegal_direction(d, movement, out, ft_ray_at(ray,
					ray_len - COL_EPSILON)));
	return (1);
}

void	ft_camera_move(t_data *d)
{
	t_camera_move_context	c;

	if (ft_get_key_down(XK_b, d))
		d->scene->camera.noclip = !d->scene->camera.noclip;
	c.campos = d->scene->camera.position;
	c.camdir = d->scene->camera.direction;
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
	c.movement.v = c.campos.v - d->scene->camera.position.v;
	if (ft_try_move(d, &c.movement))
	{
		d->dirty_frame = 1;
		d->scene->camera.position.v += c.movement.v;
	}
}

void	ft_camera_rotate(t_data *d)
{
	t_v3f	cam_rot;
	float	rotx;
	float	roty;
	float	key_rot;

	cam_rot = ft_cam_v3f_to_euler(d->scene->camera.direction);
	rotx = d->input.mouse_delta.y * CAM_ROTATION_SPEED * (d->scene->camera.fov
			/ 85.0f);
	key_rot = (float)-ft_get_key(XK_i, d) + (float)ft_get_key(XK_k, d);
	rotx += key_rot * d->deltatime * CAM_ROTATION_SPEED_KEY;
	roty = d->input.mouse_delta.x * CAM_ROTATION_SPEED * (d->scene->camera.fov
			/ 85.0);
	key_rot = (float)-ft_get_key(XK_j, d) + (float)ft_get_key(XK_l, d);
	roty += key_rot * d->deltatime * CAM_ROTATION_SPEED_KEY;
	cam_rot.x = ft_clampd(cam_rot.x + rotx, -85.0, 85.0);
	cam_rot.y = cam_rot.y + roty;
	while (cam_rot.y < -180.0)
		cam_rot.y += 360.0;
	while (cam_rot.y > 180.0)
		cam_rot.y -= 360.0;
	d->scene->camera.direction = ft_cam_euler_to_v3f(cam_rot);
	if (fabs(rotx) > EPSILON || fabs(roty) > EPSILON)
		d->dirty_frame = 1;
}

void	ft_camera_zoom(t_data *d)
{
	if (ft_get_key_down(MOUSE_SCROLL_DOWN, d))
	{
		d->scene->camera.fov *= 1.05f;
		d->dirty_frame = 1;
	}
	if (ft_get_key_down(MOUSE_SCROLL_UP, d))
	{
		d->scene->camera.fov *= 0.95f;
		d->dirty_frame = 1;
	}
}
