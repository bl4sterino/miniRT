/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pberne <pberne@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/22 13:52:25 by pberne            #+#    #+#             */
/*   Updated: 2026/01/24 06:17:38 by pberne           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void	ft_render(t_data *d)
{
	d->viewport = ft_get_viewport(d->scene->camera);
	ft_clock_start(clock_render);
	ft_setup_basic_rt_tasks(d);
	ft_clock_set(clock_render);
}
