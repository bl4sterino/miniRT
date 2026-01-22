/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pberne <pberne@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/02 11:06:28 by pberne            #+#    #+#             */
/*   Updated: 2026/01/22 14:31:36 by pberne           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

int	ft_exit_hook(void *param)
{
	(void)param;
	ft_exit(EXIT_SUCCESS);
	return (0);
}

void	ft_exit_destroy_image(void *d)
{
	mlx_destroy_image(((t_data *)d)->mlx, ((t_data *)d)->image.ptr);
}

void	ft_exit_destroy_window(void *d)
{
	mlx_destroy_window(((t_data *)d)->mlx, ((t_data *)d)->window);
}

void	ft_exit_destroy_display(void *d)
{
	mlx_destroy_display(d);
}

void	ft_exit_autorepeaton(void *d)
{
	mlx_do_key_autorepeaton(d);
}
