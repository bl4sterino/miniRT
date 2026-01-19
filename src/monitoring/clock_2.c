/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clock_2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pberne <pberne@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/19 10:50:35 by pberne            #+#    #+#             */
/*   Updated: 2026/01/19 11:36:20 by pberne           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "monitoring.h"
#include "rt.h"

double	ft_clock(int type, t_clock_name name);

void	ft_clock_start(t_clock_name name)
{
	ft_clock(CLOCK_START, name);
}

void	ft_clock_set(t_clock_name name)
{
	ft_clock(CLOCK_SET, name);
}

double	ft_clock_get(t_clock_name name)
{
	return (ft_clock(CLOCK_GET, name));
}

void	ft_clock_clear(void)
{
	ft_clock(CLOCK_CLEAR, 0);
}

double	ft_clock_set_and_get(t_clock_name name)
{
	return (ft_clock(CLOCK_SET_GET, name));
}
