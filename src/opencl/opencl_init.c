/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   opencl_init.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pberne <pberne@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/22 22:05:51 by pberne            #+#    #+#             */
/*   Updated: 2026/02/26 14:21:57 by pberne           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void	ft_get_opencl_device(t_data *d)
{
	cl_uint			num_platforms;
	cl_platform_id	*platforms;
	cl_uint			num_devices;
	cl_device_id	*devices;

	clGetPlatformIDs(0, NULL, &num_platforms);
	if (num_platforms == 0)
		ft_exit_str_fd(1, "No opencl device found\n", 2);
	platforms = ft_malloc(sizeof(cl_platform_id) * num_platforms);
	clGetPlatformIDs(num_platforms, platforms, NULL);
	d->opencl.platform = platforms[0];
	clGetDeviceIDs(d->opencl.platform, CL_DEVICE_TYPE_GPU, 0, NULL,
		&num_devices);
	devices = ft_malloc(sizeof(cl_device_id) * num_devices);
	clGetDeviceIDs(d->opencl.platform, CL_DEVICE_TYPE_GPU, num_devices, devices,
		NULL);
	d->opencl.device = devices[0];
}

void	ft_build_opencl_program_2(t_data *d)
{
	cl_int	err;

	err = clBuildProgram(d->opencl.program, 1, &d->opencl.device, 0, 0, 0);
	if (err != CL_SUCCESS)
	{
		ft_printf("Error building program: %s\n", get_cl_error(err));
		ft_exit(1);
	}
	d->opencl.command_queue = clCreateCommandQueueWithProperties(
			d->opencl.context,
			d->opencl.device, 0, &err);
	if (err != CL_SUCCESS)
		ft_printf("Error Creating Command Queue: %s\n", get_cl_error(err));
	ft_printf("Opencl build success\n");
}

void	ft_build_opencl_program(t_data *d, char *prg_str, int err)
{
	prg_str = ft_read_file_gc_id("src/rendering/post_processing.cl", 0);
	if (!prg_str)
		ft_exit_str_fd(1, "Failed to load OpenCl kernel source\n", 2);
	d->opencl.context = clCreateContext(0, 1, &d->opencl.device, 0, 0, &err);
	if (err != CL_SUCCESS)
	{
		ft_printf("Error Creating context: %s\n", get_cl_error(err));
		ft_exit(1);
	}
	d->opencl.program = clCreateProgramWithSource(d->opencl.context, 1,
			(const char **)&prg_str, 0, &err);
	if (err != CL_SUCCESS)
	{
		ft_printf("Error Creating program with source: %s\n",
			get_cl_error(err));
		ft_exit(1);
	}
	ft_build_opencl_program_2(d);
}

/* Does all the boilerplate */
void	ft_init_opencl(t_data *d)
{
	ft_get_opencl_device(d);
	ft_build_opencl_program(d, 0, 0);
	ft_init_opencl_data(d);
	ft_create_kernels(d);
}
