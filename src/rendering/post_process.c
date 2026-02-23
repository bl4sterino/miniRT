/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   post_process.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pberne <pberne@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/22 19:00:51 by pberne            #+#    #+#             */
/*   Updated: 2026/02/23 15:57:35 by pberne           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"


void	ft_get_averaged_frame(t_data *d)
{
	int		i;
	double	coef;

	d->frame_count += 1.0;
	coef = 1.0 / d->frame_count;
	i = 0;
	while (i < WIDTH_WIN * HEIGHT_WIN * 3)
	{
		d->image.averaged_colors[i] = fminf(1.0, (float)(d->image.accumulated_addr[i]
				* coef));
		i++;
	}
}

void	ft_post_process(t_data *d)
{
	int		i;
	t_v2i	pos;

	cl_int err = clEnqueueWriteBuffer(
		d->opencl.command_queue,
		d->opencl.accumulated_buff,
		CL_TRUE,
		0,
		HEIGHT_WIN * WIDTH_WIN * 3 * sizeof(double),
		d->image.accumulated_addr, 0, 0, 0);
	if(err != CL_SUCCESS)
		ft_printf("Error updating the buffer");


	d->frame_count += 1.0;
	double coef = 1.0 / d->frame_count;
	clSetKernelArg(d->opencl.kernel_average, 2, sizeof(double), &coef);
	
	size_t size = HEIGHT_WIN * WIDTH_WIN * 3;
	clEnqueueNDRangeKernel(d->opencl.command_queue, d->opencl.kernel_average, 1, 0, &size, 0, 0, 0, 0);
	err = clEnqueueReadBuffer(
	d->opencl.command_queue,
	d->opencl.a,
	CL_TRUE,
	0,
	HEIGHT_WIN * WIDTH_WIN * 3 * sizeof(double),
	d->image.averaged_colors, 0, 0, 0);
	
	clFinish(d->opencl.command_queue);

	//ft_get_averaged_frame(d);
	i = 0;
	pos.y = 0;
	while (pos.y < HEIGHT_WIN)
	{
		pos.x = 0;
		while (pos.x < WIDTH_WIN)
		{
			ft_put_pxl(d->image.addr, pos,
				ft_doubles_to_int_color(d->image.averaged_colors[i],
					d->image.averaged_colors[i + 1], d->image.averaged_colors[i
					+ 2]));
			i += 3;
			pos.x++;
		}
		pos.y++;
	}
}
