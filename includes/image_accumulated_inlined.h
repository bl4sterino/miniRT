/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   image_accumulated_inlined.h                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pberne <pberne@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/19 16:52:50 by pberne            #+#    #+#             */
/*   Updated: 2026/04/09 17:45:57 by pberne           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef IMAGE_ACCUMULATED_INLINED_H
# define IMAGE_ACCUMULATED_INLINED_H

# include "rt.h"

static inline void	ft_add_pixel_to_accumulated_image(t_data *d,
		t_thread_render_context *c, t_v3f color, int eye_id)
{
	t_v2i	pos;

	pos = c->pixel;
	if (eye_id == 0)
		d->image.current_frame[c->index].v += color.v;
	else if (eye_id == EYE_LEFT)
		d->image.current_frame[(pos.y + c->cam.rect.y) * WIDTH_WIN + pos.x
			+ c->cam.rect.x].v += color.v * v3f(0.0f, 1.0f, 1.0f).v;
	else
		d->image.current_frame[(pos.y + c->cam.rect.y) * WIDTH_WIN + pos.x
			+ c->cam.rect.x].v += color.v * v3f(1.0f, 0.0f, 0.0f).v;
}

#endif
