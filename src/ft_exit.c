/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pberne <pberne@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/02 11:06:28 by pberne            #+#    #+#             */
/*   Updated: 2026/01/16 11:16:54 by pberne           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

int	ft_destroy(void *param)
{
	param = 0;
	param += 1;
	ft_exit(EXIT_SUCCESS);
	return (0);
}

void	ft_do_exit(int flag, int exitcode, t_data *data)
{
	static t_data	*d = 0;

	if (flag == 0)
	{
		d = data;
		return ;
	}
	if (flag == 1)
	{
		ft_clear_gc();
		get_next_line(-2);
		if (d->mlx)
		{
			mlx_do_key_autorepeaton(d->mlx);
			mlx_destroy_image(d->mlx, d->image.ptr);
			mlx_destroy_window(d->mlx, d->window);
			mlx_destroy_display(d->mlx);
			free(d->mlx);
		}
		exit(exitcode);
	}
}

void	ft_exit_init(t_data *d)
{
	ft_do_exit(0, 0, d);
}

void	ft_exit(int exitcode)
{
	ft_do_exit(1, exitcode, 0);
}
