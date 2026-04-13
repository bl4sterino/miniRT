/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_abs.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pberne <pberne@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/23 18:11:59 by pberne            #+#    #+#             */
/*   Updated: 2026/02/17 16:07:35 by pberne           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_ABS_H
# define FT_ABS_H

static inline int	ft_abs(int a)
{
	if (a < 0)
		return (-a);
	return (a);
}

static inline double	ft_dabs(double a)
{
	if (a < 0.0)
		return (-a);
	return (a);
}

static inline float	ft_fabs(float a)
{
	if (a < 0.0f)
		return (-a);
	return (a);
}

#endif
