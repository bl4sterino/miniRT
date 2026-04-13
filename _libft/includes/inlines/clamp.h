/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clamp.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pberne <pberne@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/29 19:44:15 by pberne            #+#    #+#             */
/*   Updated: 2026/03/06 14:37:05 by pberne           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CLAMP_H
# define CLAMP_H

static inline int	ft_clampi(int nb, int min, int max)
{
	if (nb < min)
		return (min);
	if (nb > max)
		return (max);
	return (nb);
}

static inline long	ft_clampl(long nb, long min, long max)
{
	if (nb < min)
		return (min);
	if (nb > max)
		return (max);
	return (nb);
}

static inline float	ft_clampf(float nb, float min, float max)
{
	return (__builtin_fmaxf(__builtin_fminf(nb, max), min));
}

static inline double	ft_clampd(double nb, double min, double max)
{
	if (nb < min)
		return (min);
	if (nb > max)
		return (max);
	return (nb);
}

#endif