/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_key_controls.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pberne <pberne@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/04 13:48:05 by pberne            #+#    #+#             */
/*   Updated: 2026/01/16 14:02:50 by pberne           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void	ft_controls(t_data *d)
{
	int	psign;

	psign = ft_get_key(KEY_KP_PLUS, d) - ft_get_key(KEY_KP_MINUS, d);
	if (psign != 0)
		d->cam.speed *= 1.0f + SCALING_COEF * d->deltatime * psign;
}
