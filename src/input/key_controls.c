/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_controls.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pberne <pberne@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/04 13:48:05 by pberne            #+#    #+#             */
/*   Updated: 2026/01/27 17:55:26 by pberne           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void	ft_controls(t_data *d)
{
	ft_debug_gc(d);
	if (ft_get_key_down(KEY_E, d))
		d->render_mode = !d->render_mode;
}
