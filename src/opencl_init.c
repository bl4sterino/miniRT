/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   opencl_init.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pberne <pberne@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/22 22:05:51 by pberne            #+#    #+#             */
/*   Updated: 2026/02/25 16:45:15 by pberne           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

const char	*get_cl_error(cl_int error)
{
	switch (error)
	{
	// Segmentation/Initialization Errors
	case 0:
		return ("CL_SUCCESS");
	case -1:
		return ("CL_DEVICE_NOT_FOUND");
	case -2:
		return ("CL_DEVICE_NOT_AVAILABLE");
	case -3:
		return ("CL_COMPILER_NOT_AVAILABLE");
	case -4:
		return ("CL_MEM_OBJECT_ALLOCATION_FAILURE");
	case -5:
		return ("CL_OUT_OF_RESOURCES");
	case -6:
		return ("CL_OUT_OF_HOST_MEMORY");
	// Argument/Kernel Errors
	case -30:
		return ("CL_INVALID_VALUE");
	case -34:
		return ("CL_INVALID_CONTEXT");
	case -36:
		return ("CL_INVALID_COMMAND_QUEUE");
	case -38:
		return ("CL_INVALID_MEM_OBJECT");
	case -48:
		return ("CL_INVALID_KERNEL");
	case -52:
		return ("CL_INVALID_KERNEL_ARGS");
	case -54:
		return ("CL_INVALID_WORK_GROUP_SIZE");
	// Program/Build Errors
	case -11:
		return ("CL_BUILD_PROGRAM_FAILURE");
	case -42:
		return ("CL_INVALID_BINARY");
	default:
		return ("UNKNOWN_OPENCL_ERROR");
	}
}

void	ft_init_blur_kernel(t_data *d)
{
	cl_int	err;

	d->opencl.kernel_blur_h = clCreateKernel(d->opencl.program,
			"ft_blur_horizontal", &err);
	if (err != CL_SUCCESS)
	{
		ft_printf("Error Creating H_blur kernel: %s\n", get_cl_error(err));
		ft_exit(1);
	}
	err = clSetKernelArg(d->opencl.kernel_blur_h, 5, sizeof(cl_mem),
			&d->opencl.normals_buff);
	if (err != CL_SUCCESS)
	{
		ft_printf("Error Setting kernel arg 1: %s\n", get_cl_error(err));
		ft_exit(1);
	}


	d->opencl.kernel_blur_v = clCreateKernel(d->opencl.program,
			"ft_blur_vertical", &err);
	if (err != CL_SUCCESS)
	{
		ft_printf("Error Creating V_blur kernel: %s\n", get_cl_error(err));
		ft_exit(1);
	}
	err = clSetKernelArg(d->opencl.kernel_blur_v, 5, sizeof(cl_mem),
			&d->opencl.normals_buff);
	if (err != CL_SUCCESS)
	{
		ft_printf("Error Setting kernel arg 1: %s\n", get_cl_error(err));
		ft_exit(1);
	}
}



void	ft_init_opencl_data(t_data *d)
{
	cl_int	err;

	d->opencl.a = clCreateBuffer(d->opencl.context, CL_MEM_READ_WRITE,
			HEIGHT_WIN * WIDTH_WIN * 4 * sizeof(float), 0, &err);
	if (err != CL_SUCCESS)
	{
		ft_printf("Error Creating buffer a: %s\n", get_cl_error(err));
		ft_exit(1);
	}
	d->opencl.b = clCreateBuffer(d->opencl.context, CL_MEM_READ_WRITE,
			HEIGHT_WIN * WIDTH_WIN * 4 * sizeof(float), 0, &err);
	if (err != CL_SUCCESS)
	{
		ft_printf("Error Creating buffer b: %s\n", get_cl_error(err));
		ft_exit(1);
	}
	d->opencl.normals_buff = clCreateBuffer(d->opencl.context, CL_MEM_READ_WRITE,
			HEIGHT_WIN * WIDTH_WIN * 4 * sizeof(float), 0, &err);
	if (err != CL_SUCCESS)
	{
		ft_printf("Error Creating buffer normals: %s\n", get_cl_error(err));
		ft_exit(1);
	}
}

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
	d->opencl.command_queue = clCreateCommandQueueWithProperties(d->opencl.context,
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

void	ft_init_opencl(t_data *d)
{
	ft_get_opencl_device(d);
	ft_build_opencl_program(d, 0, 0);
	ft_init_opencl_data(d);
	ft_init_blur_kernel(d);
}
