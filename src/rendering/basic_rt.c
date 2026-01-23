/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   basic_rt.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pberne <pberne@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/23 10:35:52 by pberne            #+#    #+#             */
/*   Updated: 2026/01/23 11:49:40 by pberne           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

int	ft_get_ray_color(t_ray ray, t_scene *scene)
{
	(void)ray;
	(void)scene;
	t_sphere *spheres = scene->spheres;
	int i = 0;
	double bestdist = 999999999999;
	double dist;
	int best_i = -1;
	while (i < scene->num_spheres)
	{
		dist = ft_sphere_collision(ray, spheres[i]);
		if (dist >= 0 && dist < bestdist)
		{
			bestdist = dist;
			best_i = i;
		}
		i++;
	}
	if (best_i >= 0)
		return (ft_v3d_to_int_color(scene->spheres[best_i].color));
	return (0);
}

void	ft_basic_rt(t_viewport viewport, t_data *d)
{
	t_v2i	pixel;
	t_ray	ray;
	t_v3d	y_target;
	t_v3d	target;

	ray.origin = d->scene->camera.position;
	pixel.y = 0;
	y_target = viewport.top_left;
	while (pixel.y < HEIGHT_WIN)
	{
		pixel.x = 0;
		target = y_target;
		while (pixel.x < WIDTH_WIN)
		{
			ray.direction = ft_v3d_sub(target, ray.origin);
			ft_put_pxl(d->image.addr, pixel, ft_get_ray_color(ray, (d->scene)));
			target = ft_v3d_add(target, viewport.x_delta);
			pixel.x++;
		}
		y_target = ft_v3d_add(y_target, viewport.y_delta);
		pixel.y++;
	}
}
