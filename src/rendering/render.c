/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pberne <pberne@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/22 13:52:25 by pberne            #+#    #+#             */
/*   Updated: 2026/01/23 15:26:25 by pberne           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void	ft_render(t_data *d)
{
	t_viewport	viewport;

	viewport = ft_get_viewport(d->scene->camera);
	ft_clock_start(clock_render);
	ft_basic_rt(viewport, d);
	ft_clock_set(clock_render);
}
