/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pberne <pberne@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/02 11:06:28 by pberne            #+#    #+#             */
/*   Updated: 2026/01/24 08:40:46 by pberne           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void	ft_exit_destroy_done_cond(void *d)
{
	pthread_cond_destroy(&((t_data *)d)->threads_data.done_cond);
}

void	ft_exit_destroy_task_cond(void *d)
{
	pthread_cond_destroy(&((t_data *)d)->threads_data.task_cond);
}

void	ft_exit_destroy_task_mutex(void *d)
{
	pthread_mutex_destroy(&((t_data *)d)->threads_data.task_mutex);
}

void ft_exit_thread_cancel(void *d)
{
	t_data *data;
	void *ret;

	int i = 0;
	data = d;
	data->threads_data.run_threads = -1;
	pthread_cond_broadcast(&data->threads_data.task_cond);
	while (i < data->threads_data.count)
	{
		pthread_join(data->threads_data.threads[i], &ret);
		i++;
	}
}
