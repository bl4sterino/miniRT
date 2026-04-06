/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pberne <pberne@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/30 11:19:00 by pberne            #+#    #+#             */
/*   Updated: 2026/04/06 19:39:11 by tpotier          ###   ########.fr       */
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
	ft_add_exit(d.mlx, free);
	ft_add_exit(d.mlx, ft_exit_destroy_display);
	d.scene = ft_parse_map(&d, av[1]);
	recompute_grid(d.scene, (t_rect){0, 0, WIDTH_WIN, HEIGHT_WIN});
	d.viewports = ft_malloc(sizeof(*d.viewports) * d.scene->num_cameras);
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
