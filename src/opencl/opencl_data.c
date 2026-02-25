/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   opencl_data.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pberne <pberne@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/25 21:49:01 by pberne            #+#    #+#             */
/*   Updated: 2026/02/25 22:32:04 by pberne           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void	ft_init_opencl_data_3(t_data *d)
{
	cl_int	err;

	d->opencl.normals_buff = clCreateBuffer(d->opencl.context,
			CL_MEM_READ_WRITE, HEIGHT_WIN * WIDTH_WIN * 4 * sizeof(float), 0,
			&err);
	if (err != CL_SUCCESS)
	{
		ft_printf("Error, normals_buff: %s\n", get_cl_error(err));
		ft_exit(1);
	}
	d->opencl.depth_buff = clCreateBuffer(d->opencl.context, CL_MEM_READ_WRITE,
			HEIGHT_WIN * WIDTH_WIN * sizeof(double), 0, &err);
	if (err != CL_SUCCESS)
	{
		ft_printf("Error, depth_buff: %s\n", get_cl_error(err));
		ft_exit(1);
	}
}

void	ft_init_opencl_data_2(t_data *d)
{
	cl_int	err;

	d->opencl.a = clCreateBuffer(d->opencl.context, CL_MEM_READ_WRITE,
			HEIGHT_WIN * WIDTH_WIN * 4 * sizeof(float), 0, &err);
	if (err != CL_SUCCESS)
	{
		ft_printf("Error, a: %s\n", get_cl_error(err));
		ft_exit(1);
	}
	d->opencl.b = clCreateBuffer(d->opencl.context, CL_MEM_READ_WRITE,
			HEIGHT_WIN * WIDTH_WIN * 4 * sizeof(float), 0, &err);
	if (err != CL_SUCCESS)
	{
		ft_printf("Error, b: %s\n", get_cl_error(err));
		ft_exit(1);
	}
	ft_init_opencl_data_3(d);
}

void	ft_init_opencl_data(t_data *d)
{
	cl_int	err;

	d->opencl.frame_buff = clCreateBuffer(d->opencl.context, CL_MEM_READ_WRITE,
			HEIGHT_WIN * WIDTH_WIN * 4 * sizeof(float), 0, &err);
	if (err != CL_SUCCESS)
	{
		ft_printf("Error, frame_buff: %s\n", get_cl_error(err));
		ft_exit(1);
	}
	d->opencl.accumulated_buff = clCreateBuffer(d->opencl.context,
			CL_MEM_READ_WRITE, HEIGHT_WIN * WIDTH_WIN * 4 * sizeof(float), 0,
			&err);
	if (err != CL_SUCCESS)
	{
		ft_printf("Error, accumulated_buff: %s\n", get_cl_error(err));
		ft_exit(1);
	}
	d->opencl.out_packed_buff = clCreateBuffer(d->opencl.context,
			CL_MEM_READ_WRITE, HEIGHT_WIN * WIDTH_WIN * sizeof(int), 0, &err);
	if (err != CL_SUCCESS)
	{
		ft_printf("Error, out_packed_buff: %s\n", get_cl_error(err));
		ft_exit(1);
	}
	ft_init_opencl_data_2(d);
}
