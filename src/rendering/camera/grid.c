/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   grid.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pberne <pberne@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/06 15:34:00 by tpotier           #+#    #+#             */
/*   Updated: 2026/04/08 14:40:44 by pberne           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void	refresh_grid(t_data *d)
{
	recompute_grid(d->scene, (t_rect){0, 0, WIDTH_WIN, HEIGHT_WIN});
	ft_free(d->viewports);
	d->viewports = ft_malloc(sizeof(*d->viewports) * d->scene->num_cameras);
	d->dirty_frame = 1;
}

// FIXME: store/double capacity
void	add_camera(t_scene *scene, t_camera *cam)
{
	t_camera	*new;
	t_camera	*old;

	if (scene->num_cameras >= 65025)
		return ;
	new = ft_malloc(sizeof(*new) * (scene->num_cameras + 1));
	ft_memcpy(new, scene->cameras, sizeof(*new) * scene->num_cameras);
	old = scene->cameras;
	scene->cameras = new;
	if (cam->render_mode < 0 || cam->render_mode > RENDER_NORMALS)
		ft_exit_str_fd(1, "Camera render mode is out of range\n", 2);
	scene->cameras[scene->num_cameras++] = *cam;
	ft_free(old);
}

void	remove_camera(t_scene *scene)
{
	if (scene->num_cameras == 1)
		return ;
	scene->num_cameras--;
	if (scene->active_camera >= scene->num_cameras)
		scene->active_camera = scene->num_cameras - 1;
}

void	recompute_grid(t_scene *scene, t_rect rect)
{
	int	s;
	int	i;
	int	grid_h;
	int	last;

	s = 1;
	while (s * s < scene->num_cameras)
		s++;
	grid_h = 1;
	while (grid_h * s < scene->num_cameras)
		grid_h++;
	last = scene->num_cameras - (grid_h - 1) * s;
	i = 0;
	while (i < scene->num_cameras)
	{
		if (i / s == grid_h - 1)
			scene->cameras[i].rect = (t_rect){.x = (i % s) * (rect.w / last),
				.y = (i / s) * (rect.h / grid_h), .w = rect.w / last,
				.h = rect.h / grid_h};
		else
			scene->cameras[i].rect = (t_rect){.x = (i % s) * (rect.w / s),
				.y = (i / s) * (rect.h / grid_h), .w = rect.w / s, .h = rect.h
				/ grid_h};
		i++;
	}
}
