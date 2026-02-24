/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   post_process.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pberne <pberne@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/22 19:00:51 by pberne            #+#    #+#             */
/*   Updated: 2026/02/24 10:11:21 by pberne           ###   ########.fr       */
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

void ft_average(t_data *d)
{
	cl_int err = clEnqueueWriteBuffer(
		d->opencl.command_queue,
		d->opencl.accumulated_buff,
		CL_TRUE,
		0,
		HEIGHT_WIN * WIDTH_WIN * 3 * sizeof(double),
		d->image.accumulated_addr, 0, 0, 0);
	if(err != CL_SUCCESS)
	{
		ft_printf("Error updating the buffer\n");
		ft_exit(1);
	}
		
	d->frame_count += 1.0;
	double coef = 1.0 / d->frame_count;
	clSetKernelArg(d->opencl.kernel_average, 2, sizeof(double), &coef);
	
	size_t size = (HEIGHT_WIN * WIDTH_WIN) * 3 / 32;
	clEnqueueNDRangeKernel(d->opencl.command_queue, d->opencl.kernel_average, 1, 0, &size, 0, 0, 0, 0);
	
	clFinish(d->opencl.command_queue);
}

void ft_blur(t_data *d)
{
	int err = clSetKernelArg(d->opencl.kernel_blur, 0, sizeof(cl_mem),
			&d->opencl.a);
	if (err != CL_SUCCESS)
	{
		ft_printf("Error Setting kernel arg 0: %s\n", get_cl_error(err));
		ft_exit(1);
	}

	err = clSetKernelArg(d->opencl.kernel_blur, 1, sizeof(cl_mem),
			&d->opencl.b);
	if (err != CL_SUCCESS)
	{
		ft_printf("Error Setting kernel arg 1: %s\n", get_cl_error(err));
		ft_exit(1);
	}
	
	size_t size[2] = {WIDTH_WIN * 3, HEIGHT_WIN};
	clEnqueueNDRangeKernel(d->opencl.command_queue, d->opencl.kernel_blur, 2, 0, &size, 0, 0, 0, 0);

	clFinish(d->opencl.command_queue);
}

void	ft_post_process(t_data *d)
{
	int		i;
	t_v2i	pos;

	ft_average(d);
	
	ft_blur(d);
	

	int err = clEnqueueReadBuffer(
		d->opencl.command_queue,
		d->opencl.b,
		CL_TRUE,
		0,
		HEIGHT_WIN * WIDTH_WIN * 3 * sizeof(double),
		d->image.averaged_colors, 0, 0, 0);


	clFinish(d->opencl.command_queue);


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
