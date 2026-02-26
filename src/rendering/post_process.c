/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   post_process.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pberne <pberne@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/22 19:00:51 by pberne            #+#    #+#             */
/*   Updated: 2026/02/26 16:27:23 by pberne           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void ft_set_and_pack(t_data *d)
{
	cl_int err;
	size_t size;
	
	err = clSetKernelArg(d->opencl.kernel_set_and_pack, 0, sizeof(cl_mem), &d->opencl.a);
	if (err != CL_SUCCESS)
	{
		ft_printf("Error Setting set arg\n");
		ft_exit(1);
	}

	size = WIDTH_WIN * HEIGHT_WIN;
	err = clEnqueueNDRangeKernel(d->opencl.command_queue, d->opencl.kernel_set_and_pack, 1,
		0, &size, 0, 0, 0, 0);
	clFinish(d->opencl.command_queue);
}

void ft_accumulate_and_pack(t_data *d)
{
	cl_int err;
	size_t size;
	
	err = clSetKernelArg(d->opencl.kernel_accumulate_and_pack, 0, sizeof(cl_mem), &d->opencl.a);

	d->frame_count += 1.0;
	float coef = (float)(1.0 / d->frame_count);
	err += clSetKernelArg(d->opencl.kernel_accumulate_and_pack, 3, sizeof(float), &coef);

	if (err != CL_SUCCESS)
	{
		ft_printf("Error Setting acc arg\n");
		ft_exit(1);
	}

	size = WIDTH_WIN * HEIGHT_WIN;
	err = clEnqueueNDRangeKernel(d->opencl.command_queue, d->opencl.kernel_accumulate_and_pack, 1,
		0, &size, 0, 0, 0, 0);
	clFinish(d->opencl.command_queue);
}

void	ft_blur_kernel(t_data *d, cl_kernel blur_kernel, int radius, int spacing)
{
	int		err;
	size_t	size[2] = {WIDTH_WIN, HEIGHT_WIN};
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
		ft_printf("Err blur exec; %s\n", get_cl_error(err));
	err = clSetKernelArg(blur_kernel, 3, sizeof(int), &spacing);
	if(err != CL_SUCCESS)
		ft_printf("Err blur exec; %s\n", get_cl_error(err));

	err = clSetKernelArg(blur_kernel, 4, sizeof(cl_mem), &d->opencl.gaussian_mat);
	if(err != CL_SUCCESS)
		ft_printf("Err blur exec; %s\n", get_cl_error(err));

	err = clEnqueueNDRangeKernel(d->opencl.command_queue, blur_kernel, 2,
		0, (void *)(&size), 0, 0, 0, 0);
	if(err != CL_SUCCESS)
		ft_printf("Err blur exec; %s\n", get_cl_error(err));
	clFinish(d->opencl.command_queue);
	
	temp = d->opencl.a;
	d->opencl.a = d->opencl.b;
	d->opencl.b = temp;
}

void	ft_update_gaussian_mat(t_data *d, int radius)
{
	int		size;
	int		i;
	float	sum;
	float	sigma;
	float *gaussian_mat;
	int err;

	size = radius * 2 + 1;
	gaussian_mat = malloc(sizeof(float) * size);
	if (!gaussian_mat)
		ft_exit(MALLOC_FAILED);
	i = 0;
	sum = 0.0f;
	sigma = (double)radius / 2.0f;
	while (i < size)
	{
		gaussian_mat[i] = expf(-(float)((i - radius) * (i - radius)) / (2.0f
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

	d->opencl.gaussian_mat = clCreateBuffer(d->opencl.context, CL_MEM_READ_ONLY | CL_MEM_COPY_HOST_PTR, size * sizeof(float), gaussian_mat, &err);
	if (err != CL_SUCCESS)
	{
		free(gaussian_mat);
		ft_printf("Failed to create gaussiant_mat buffer: %s\n", get_cl_error(err));
	}
	free(gaussian_mat);
}

void	ft_blur(t_data *d)
{
	int radius;
	int space;
	cl_int err;

	err = 0;
	ft_clock_start(clock_blur);
	if (d->denoise)
	{
		err = clEnqueueWriteBuffer(d->opencl.command_queue,
			d->opencl.normals_buff, CL_TRUE, 0, HEIGHT_WIN * WIDTH_WIN * 4
			* sizeof(double), d->image.normals, 0, 0, 0);
		if (err != CL_SUCCESS)
			ft_printf("Error write normals top gpu\n");
		radius = 3;
		space = 1;
		ft_update_gaussian_mat(d, radius);
		ft_blur_kernel(d, d->opencl.kernel_blur_h, radius, space);
		ft_blur_kernel(d, d->opencl.kernel_blur_v, radius, space);
	}
	ft_clock_set(clock_blur);
}

void ft_process_normals(t_data *d)
{
	cl_int err;
	size_t size;

	clSetKernelArg(d->opencl.kernel_process_normals, 0, sizeof(cl_mem),
			&d->opencl.a);
	size = WIDTH_WIN * HEIGHT_WIN;
	err = clEnqueueNDRangeKernel(d->opencl.command_queue, d->opencl.kernel_process_normals, 1,
		0, &size, 0, 0, 0, 0);
	if (err != CL_SUCCESS)
			ft_printf("Error processing normals\n");
	clFinish(d->opencl.command_queue);

}

void	ft_post_process(t_data *d)
{
	int		i;
	t_v2i	pos;
	int		err;

	if (d->render_mode == RENDER_NORMALS)
	{
		err = clEnqueueWriteBuffer(d->opencl.command_queue,
			d->opencl.a, CL_TRUE, 0, HEIGHT_WIN * WIDTH_WIN * 4
			* sizeof(float), d->image.normals, 0, 0, 0);
		ft_process_normals(d);
	}
		
	else
		err = clEnqueueWriteBuffer(d->opencl.command_queue,
			d->opencl.a, CL_TRUE, 0, HEIGHT_WIN * WIDTH_WIN * 4
			* sizeof(float), d->image.current_frame, 0, 0, 0);

	ft_blur(d);


	if (d->dirty_frame)
	{
		ft_set_and_pack(d);
		d->dirty_frame = 0;
		d->frame_count = 1.0;
	}
	else
		ft_accumulate_and_pack(d);

	err = clEnqueueReadBuffer(d->opencl.command_queue, d->opencl.out_packed_buff, CL_TRUE, 0,
			HEIGHT_WIN * WIDTH_WIN * sizeof(int),
			d->image.addr, 0, 0, 0);

	clFinish(d->opencl.command_queue);
}
