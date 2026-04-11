/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pberne <pberne@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/30 11:19:00 by pberne            #+#    #+#             */
/*   Updated: 2026/04/11 14:00:03 by pberne           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

int	ft_check_map_format(char *str)
{
	size_t	len;

	len = ft_strlen(str);
	return (len < 3 || ft_strcmp(&str[len - 3], ".rt"));
}

int	main(int ac, char **av)
{
	t_data	d;

	ft_init_data(&d);
	if (ac != 2)
		return (ft_putstr_fd("Wrong number of arguments\n", 2), 1);
	if (ft_check_map_format(av[1]))
		return (ft_putstr_fd("only .rt file sare supported\n", 1), 1);
	d.mlx = mlx_init();
	if (!d.mlx)
		ft_exit(MALLOC_FAILED);
	ft_add_exit(d.mlx, free);
	ft_add_exit(d.mlx, ft_exit_destroy_display);
	ft_clock_start(clock_loading);
	d.scene = ft_parse_map(&d, av[1]);
	refresh_grid(&d);
	ft_clear_gc_id(malloc_id_parsing);
	ft_init_thread_pool(&d);
	d.window = mlx_new_window(d.mlx, WIDTH_WIN, HEIGHT_WIN, "mini-rt");
	if (!d.window)
		ft_exit(MALLOC_FAILED);
	ft_add_exit((void *)&d, ft_exit_destroy_window);
	ft_create_image(&d);
	ft_setup_hooks(&d);
	mlx_loop(d.mlx);
	return (0);
}
