/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   post_process.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pberne <pberne@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/22 19:00:51 by pberne            #+#    #+#             */
/*   Updated: 2026/03/04 10:55:29 by pberne           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void	ft_post_process(t_data *d)
{
	int		i;
	float	coef;
	t_v3f	max;

	i = 0;
	d->frame_count += 1.0f;
	coef = 1.0f / d->frame_count;
	max = (t_v3f){{1.0, 1.0, 1.0}};
	while (i < SCREEN_SIZE)
	{
		ft_put_pxl_addr((int *)d->image.addr, i,
			ft_v3f_to_int_color(ft_v3f_min(ft_v3f_scale(d->image.current_frame[i],
						coef), max)));
		i++;
	}
}
