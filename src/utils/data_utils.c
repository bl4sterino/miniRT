/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   data_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pberne <pberne@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/23 17:07:55 by pberne            #+#    #+#             */
/*   Updated: 2026/03/23 17:12:14 by pberne           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

t_data	*ft_data(t_data *data, int set)
{
	static t_data	*d = 0;

	if (set)
		d = data;
	else
		return (d);
	return (0);
}

t_data	*ft_get_data(void)
{
	return (ft_data(0, 0));
}

void	ft_set_data(t_data *d)
{
	ft_data(d, 1);
}
