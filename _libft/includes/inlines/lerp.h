/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lerp.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pberne <pberne@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/19 16:22:16 by pberne            #+#    #+#             */
/*   Updated: 2026/01/19 16:47:51 by pberne           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LERP_H
# define LERP_H

static inline int	ft_lerpi(int a, int b, float t)
{
	return ((int)((1.0f - t) * (float)a + t * (float)b));
}

static inline float	ft_lerpf(float a, float b, float t)
{
	return ((1.0f - t) * a + t * b);
}

static inline double	ft_lerpd(double a, double b, double t)
{
	return ((1.0 - t) * a + t * b);
}

#endif
