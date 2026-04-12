/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_dof_settings.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pberne <pberne@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/12 18:42:10 by pberne            #+#    #+#             */
/*   Updated: 2026/04/12 19:17:44 by pberne           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void	ft_dof_focus_distance(t_data *d, t_camera *cam)
{
	if (ft_get_key(XK_3, d))
	{
		cam->focus_distance *= 1.0f - ft_clampf(0.5f * d->deltatime, 0.0f,
				0.5f);
		cam->dirty = 1;
	}
	if (ft_get_key(XK_4, d))
	{
		cam->focus_distance *= 1.0f + 0.5f * d->deltatime;
		cam->dirty = 1;
	}
}

void	ft_dof_aperture(t_data *d, t_camera *cam)
{
	if (ft_get_key(XK_1, d))
	{
		cam->aperture *= 1.0f - ft_clampf(0.5f * d->deltatime, 0.0f, 0.5f);
		cam->dirty = 1;
	}
	if (ft_get_key(XK_2, d))
	{
		cam->aperture *= 1.0f + 0.5f * d->deltatime;
		cam->dirty = 1;
	}
}

void	ft_dof_settings(t_data *d, t_camera *cam)
{
	if (ft_get_key_down(XK_r, d))
	{
		cam->dof = !cam->dof;
		cam->dirty = 1;
	}
	ft_dof_aperture(d, cam);
	ft_dof_focus_distance(d, cam);
}
