/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pberne <pberne@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/30 11:19:00 by pberne            #+#    #+#             */
/*   Updated: 2026/01/22 14:28:43 by pberne           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void	ft_setup_hooks(t_data *d)
{
	ft_add_exit(d->mlx, ft_exit_autorepeaton);
	mlx_do_key_autorepeatoff(d->mlx);
	mlx_hook(d->window, 2, (1L << 0), &ft_key_down, d);
	mlx_hook(d->window, 3, (1L << 1), &ft_key_up, d);
	mlx_hook(d->window, 4, (1L << 2), &ft_mouse_down, d);
	mlx_hook(d->window, 5, (1L << 3), &ft_mouse_up, d);
	mlx_hook(d->window, 17, 0L, &ft_exit_hook, d);
	mlx_loop_hook(d->mlx, &ft_exec_updates, d);
}

void	ft_data_init(t_data *d)
{
	d->mlx = 0;
	d->window = 0;
	d->image.ptr = 0;
	d->projection = 0;
	d->last_tv.tv_sec = 0;
	d->last_tv.tv_usec = 0;
	d->deltatime = 0;
	d->frame_count = 0;
	d->input.mouse_reset = 0;
	d->fpsstr = 0;
}

int	main(int ac, char **av)
{
	t_data	d;

	ft_data_init(&d);
	if (ac != 2)
		return (ft_putstr_fd("Wrong number of arguments\n", 2), 0);
	d.scene = ft_parse_map(av[1]);
	gettimeofday(&(d.last_tv), 0);
	ft_input_init(&d);
	d.mlx = mlx_init();
	if (!d.mlx)
		ft_exit(MALLOC_FAILED);
	ft_add_exit(d.mlx, free);
	ft_add_exit(d.mlx, ft_exit_destroy_display);
	d.window = mlx_new_window(d.mlx, WIDTH_WIN, HEIGHT_WIN, "mini-rt");
	if (!d.window)
		ft_exit(MALLOC_FAILED);
	ft_add_exit((void *)&d, ft_exit_destroy_window);
	ft_create_image(&d);
	ft_setup_hooks(&d);
	mlx_loop(d.mlx);
	return (0);
}
