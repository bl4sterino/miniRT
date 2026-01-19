/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clock.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pberne <pberne@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/19 10:50:35 by pberne            #+#    #+#             */
/*   Updated: 2026/01/19 11:37:46 by pberne           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "monitoring.h"
#include "rt.h"

double	ft_clock(int type, t_clock_name name)
{
	static double	clocks[CLOCK_COUNT];
	static int		init = 0;

	if (init == 0)
	{
		init = 1;
		ft_bzero(clocks, sizeof(double) * CLOCK_COUNT);
	}
	if (type == CLOCK_START)
		clocks[name] = ft_get_real_time();
	else if (type == CLOCK_SET)
		clocks[name] = clocks[name] - ft_get_real_time();
	else if (type == CLOCK_GET)
		return (clocks[name]);
	else if (type == CLOCK_SET_GET)
	{
		clocks[name] = ft_get_real_time() - clocks[name];
		return (clocks[name]);
	}
	else if (type == CLOCK_CLEAR)
		ft_bzero(clocks, sizeof(double) * CLOCK_COUNT);
	return (0);
}
