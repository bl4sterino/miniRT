/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   post_process.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pberne <pberne@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/22 19:00:51 by pberne            #+#    #+#             */
/*   Updated: 2026/02/24 16:28:59 by pberne           ###   ########.fr       */
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
		d->image.averaged_colors[i] = fminf(1.0,
				(float)(d->image.accumulated_addr[i] * coef));
		i++;
	}
}

void	ft_average(t_data *d)
{
	cl_int	err;
	double	coef;
	size_t	size;

	err = clEnqueueWriteBuffer(d->opencl.command_queue,
			d->opencl.accumulated_buff, CL_TRUE, 0, HEIGHT_WIN * WIDTH_WIN * 3
			* sizeof(double), d->image.accumulated_addr, 0, 0, 0);
	if (err != CL_SUCCESS)
	{
		ft_printf("Error updating the buffer\n");
		ft_exit(1);
	}
	d->frame_count += 1.0;
	coef = 1.0 / d->frame_count;
	clSetKernelArg(d->opencl.kernel_average, 1, sizeof(cl_mem), &d->opencl.a);
	clSetKernelArg(d->opencl.kernel_average, 2, sizeof(double), &coef);
	size = (HEIGHT_WIN * WIDTH_WIN * 3);
	clEnqueueNDRangeKernel(d->opencl.command_queue, d->opencl.kernel_average, 1,
		0, &size, 0, 0, 0, 0);
	clFinish(d->opencl.command_queue);
}

void	ft_blur_kernel(t_data *d, cl_kernel blur_kernel, int radius, int spacing)
{
	int		err;
	size_t	size[2] = {WIDTH_WIN * 3, HEIGHT_WIN};
	cl_mem	temp;

	err = clSetKernelArg(blur_kernel, 0, sizeof(cl_mem), &d->opencl.a);
	if (err != CL_SUCCESS)
	{
		ft_printf("Error Setting blur_kernel arg 0: %s\n", get_cl_error(err));
		ft_exit(1);
	}
	err = clSetKernelArg(blur_kernel, 1, sizeof(cl_mem), &d->opencl.b);
	if (err != CL_SUCCESS)
	{
		ft_printf("Error Setting blur_kernel arg 1: %s\n", get_cl_error(err));
		ft_exit(1);
	}

	err = clSetKernelArg(blur_kernel, 2, sizeof(int), &radius);
	if(err != CL_SUCCESS)
		printf("Err blur exec; %s\n", get_cl_error(err));
	err = clSetKernelArg(blur_kernel, 3, sizeof(int), &spacing);
	if(err != CL_SUCCESS)
		printf("Err blur exec; %s\n", get_cl_error(err));

	err = clSetKernelArg(blur_kernel, 4, sizeof(cl_mem), &d->opencl.gaussian_mat);
	if(err != CL_SUCCESS)
		printf("Err blur exec; %s\n", get_cl_error(err));

	err = clEnqueueNDRangeKernel(d->opencl.command_queue, blur_kernel, 2,
		0, &size, 0, 0, 0, 0);
	if(err != CL_SUCCESS)
		printf("Err blur exec; %s\n", get_cl_error(err));
	clFinish(d->opencl.command_queue);
	
	temp = d->opencl.a;
	d->opencl.a = d->opencl.b;
	d->opencl.b = temp;
}

void	ft_update_gaussian_mat(t_data *d, int radius)
{
	int		size;
	int		i;
	double	sum;
	double	sigma;
	double * gaussian_mat;
	int err;

	size = radius * 2 + 1;
	gaussian_mat = malloc(sizeof(double) * size);
	if (!gaussian_mat)
		ft_exit(MALLOC_FAILED);
	i = 0;
	sum = 0.0;
	sigma = (double)radius / 2.0;
	while (i < size)
	{
		gaussian_mat[i] = exp(-(double)((i - radius) * (i - radius)) / (2.0
					* sigma * sigma));
		sum += gaussian_mat[i];
		i++;
	}
	i = 0;
	while (i < size)
	{
		gaussian_mat[i] /= sum;
		i++;
	}
	
	if(d->opencl.gaussian_mat != 0)
	{
		clReleaseMemObject(d->opencl.gaussian_mat);
		d->opencl.gaussian_mat = 0;
	}

	d->opencl.gaussian_mat = clCreateBuffer(d->opencl.context, CL_MEM_READ_ONLY | CL_MEM_COPY_HOST_PTR, size * sizeof(double), gaussian_mat, &err);
	if (err != CL_SUCCESS)
	{
		free(gaussian_mat);
		printf("Failed to create gaussiant_mat buffer: %s\n", get_cl_error(err));
	}
	free(gaussian_mat);
}

void	ft_blur(t_data *d)
{
	int radius;
	int space;
	int err;

	//ft_clock_start(clock_blur);
	if (d->denoise)
	{
		radius = 4;
		space = 1;
		
		ft_update_gaussian_mat(d, radius);
		ft_blur_kernel(d, d->opencl.kernel_blur_h, radius, space);
		ft_blur_kernel(d, d->opencl.kernel_blur_v, radius, space);

		space = 2;
		ft_blur_kernel(d, d->opencl.kernel_blur_h, radius, space);
		ft_blur_kernel(d, d->opencl.kernel_blur_v, radius, space);

		space = 3;
		ft_blur_kernel(d, d->opencl.kernel_blur_h, radius, space);
		ft_blur_kernel(d, d->opencl.kernel_blur_v, radius, space);
	}
}

void	ft_post_process(t_data *d)
{
	int		i;
	t_v2i	pos;
	int		err;

	ft_average(d);
	ft_blur(d);

	err = clEnqueueReadBuffer(d->opencl.command_queue, d->opencl.a, CL_TRUE, 0,
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
