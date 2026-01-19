/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   image2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pberne <pberne@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/06 19:44:09 by pberne            #+#    #+#             */
/*   Updated: 2026/01/19 17:31:00 by pberne           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

int	ft_color_lerp_rgb_to_int(t_rgb c1, t_rgb c2, float t)
{
	t_rgb	ret;

	ret = (t_rgb){ft_lerpi(c1.r, c2.r, t), ft_lerpi(c1.g, c2.g, t),
		ft_lerpi(c1.b, c2.b, t)};
	return (ret.r << 16 | ret.g << 8 | ret.b);
}

int	ft_uc_color_to_int(unsigned char r, unsigned char g, unsigned char b)
{
	return (r << 16 | g << 8 | b);
}
