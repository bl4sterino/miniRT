/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_key_controls.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pberne <pberne@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/04 13:48:05 by pberne            #+#    #+#             */
/*   Updated: 2026/01/16 11:14:22 by pberne           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void	ft_controls(t_data *d)
{
	int	psign;

	psign = ft_get_key(KEY_KP_PLUS, d) - ft_get_key(KEY_KP_MINUS, d);
	if (psign != 0)
	{
		d->cam.speed *= 1.0f + SCALING_COEF * d->deltatime * psign;
	}
	if (ft_get_key(KEY_Q, d) - ft_get_key(KEY_E, d) != 0)
		ft_multiply_z(d, -ft_get_key(KEY_Q, d) + ft_get_key(KEY_E, d));
	if (ft_get_key_down(KEY_KP_0, d))
		ft_reset_model_rotation(d);
}
