/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   image_accumulated_inlined.h                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pberne <pberne@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/19 16:52:50 by pberne            #+#    #+#             */
/*   Updated: 2026/04/08 16:55:51 by pberne           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef IMAGE_ACCUMULATED_INLINED_H
# define IMAGE_ACCUMULATED_INLINED_H

# include "rt.h"

static inline void	ft_add_pixel_to_accumulated_image(t_data *d, int index,
		t_v3f color, int eye_id)
{
	if (eye_id == 0)
		d->image.current_frame[index].v += color.v;
	else if (eye_id == EYE_LEFT)
		d->image.current_frame[index].v += color.v * v3f(0.0f, 1.0f, 1.0f).v;
	else
		d->image.current_frame[index].v += color.v * v3f(1.0f, 0.0f, 0.0f).v;
}

#endif
