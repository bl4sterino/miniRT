/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   image_accumulated_inlined.h                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pberne <pberne@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/19 16:52:50 by pberne            #+#    #+#             */
/*   Updated: 2026/02/21 13:54:11 by pberne           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef IMAGE_ACCUMULATED_INLINED_H
# define IMAGE_ACCUMULATED_INLINED_H

# include "rt.h"

static inline void	ft_add_pixel_to_accumulated_image(t_data *d, t_v2i pos,
		t_v3d color)
{
	int	index;

	index = (pos.y * WIDTH_WIN + pos.x) * 3;
	d->image.accumulated_addr[index] += color.x;
	d->image.accumulated_addr[index + 1] += color.y;
	d->image.accumulated_addr[index + 2] += color.z;
}

#endif