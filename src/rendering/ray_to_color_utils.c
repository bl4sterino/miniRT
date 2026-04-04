/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_to_color_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pberne <pberne@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/04 21:25:15 by pberne            #+#    #+#             */
/*   Updated: 2026/04/04 21:25:22 by pberne           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

t_v3f	ft_get_sky_color(t_scene *scene, t_ray ray, t_out_buffer *out)
{
	if (out)
		*out = (t_out_buffer){ray.direction};
	if (scene->skybox_tex.hdr_pixels)
	{
		if (ray.diffused)
			return (ft_sample_texture_hdr(&scene->skybox_tex,
					ft_sphere_uv(ray.direction, scene->skybox_sphere)));
		else
			return (ft_sample_texture(&scene->skybox_tex,
					ft_sphere_uv(ray.direction, scene->skybox_sphere)));
	}
	return (scene->ambient_light.color);
}
