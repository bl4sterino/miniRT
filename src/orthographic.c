/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_orthographic.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pberne <pberne@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/03 11:01:49 by pberne            #+#    #+#             */
/*   Updated: 2025/12/06 19:47:35 by pberne           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

t_screenpoint	ft_project_isometric_point(t_v3f cameraSpace, float scale)
{
	t_screenpoint	sp;
	float			sx;
	float			sy;

	sp.depth = cameraSpace.y;
	sx = cameraSpace.x * scale;
	sy = cameraSpace.z * scale;
	sp.x = sx + (WIDTH_WIN / 2.0f);
	sp.y = sy + (HEIGHT_WIN / 2.0f);
	return (sp);
}
