/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pberne <pberne@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/30 11:19:00 by pberne            #+#    #+#             */
/*   Updated: 2026/01/24 08:50:26 by pberne           ###   ########.fr       */
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

// TODO dynamic thread count
void	ft_init_thread_pool(t_data *d)
{
	int	i;
	int	count;

	if (pthread_mutex_init(&(d->threads_data.task_mutex), NULL) != 0)
		ft_exit(1);
	ft_add_exit(d, ft_exit_destroy_task_mutex);
	if (pthread_cond_init(&(d->threads_data.task_cond), NULL) != 0)
		ft_exit(1);
	ft_add_exit(d, ft_exit_destroy_task_cond);
	if (pthread_cond_init(&(d->threads_data.done_cond), NULL) != 0)
		ft_exit(1);
	ft_add_exit(d, ft_exit_destroy_done_cond);
	count = sysconf(_SC_NPROCESSORS_ONLN);
	d->threads_data.tasks = ft_malloc(sizeof(t_render_task)
			* count);
	d->threads_data.threads = ft_malloc(sizeof(pthread_t)
			* count);
	i = 0;
	while (i < count)
	{
		if (pthread_create(&(d->threads_data.threads[i]), NULL, ft_thread_loop,
				d) != 0)
		{
			ft_add_exit(d, ft_exit_thread_cancel);
			ft_exit(1);
		}
		else
			d->threads_data.count += 1;
		i++;
	}
	ft_add_exit(d, ft_exit_thread_cancel);
}

int	main(int ac, char **av)
{
	t_data	d;

	ft_bzero(&d, sizeof(t_data));
	gettimeofday(&(d.last_tv), 0);
	if (ac != 2)
		return (ft_putstr_fd("Wrong number of arguments\n", 2), 0);
	d.scene = ft_parse_map(av[1]);
	ft_clear_gc_id(malloc_id_parsing);
	ft_input_init(&d);
	ft_init_thread_pool(&d);
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
