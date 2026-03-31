/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bvh.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pberne <pberne@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/31 13:52:07 by pberne            #+#    #+#             */
/*   Updated: 2026/03/31 14:19:00 by pberne           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

int	main(int ac, char **av)
{
	t_data	d;

	ft_init_data(&d);
	if (ac != 2)
		return (ft_putstr_fd("Wrong number of arguments\n", 2), 0);
	d.mlx = mlx_init();
	if (!d.mlx)
		ft_exit(MALLOC_FAILED);
	d.scene = ft_parse_map(&d, av[1]);
	ft_exit(0);
}
