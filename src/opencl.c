/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   opencl.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pberne <pberne@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/22 22:05:51 by pberne            #+#    #+#             */
/*   Updated: 2026/02/22 23:28:15 by pberne           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void	ft_init_opencl(t_data *d)
{
	cl_uint			num_platforms;
	cl_platform_id	*platforms;

	clGetPlatformIDs(0, NULL, &num_platforms);
	platforms = ft_malloc(sizeof(cl_platform_id) * num_platforms);
	clGetPlatformIDs(num_platforms, platforms, NULL);
	cl_platform_id platform = platforms[0];

	cl_uint num_devices;
	clGetDeviceIDs(platform, CL_DEVICE_TYPE_GPU, 0, NULL, &num_devices);
	cl_device_id devices[num_devices];
	clGetDeviceIDs(platform, CL_DEVICE_TYPE_GPU, num_devices, devices, NULL);
	cl_device_id device = devices[0];


	char *prg_str = ft_read_file_gc_id("src/rendering/post_processing.cl", 0);
	if(!prg_str)
		ft_exit_str_fd(1, "Failed to load OpenCl kernel source\n", 2);
	int err;

	cl_context context = clCreateContext(0, 1, &device, 0, 0, &err);
	ft_printf("Created context, err: %d\n", err);
	
	cl_program program = clCreateProgramWithSource(context, 1, &prg_str, 0, &err);
		ft_printf("Created program, err: %d\n", err);

	cl_int build_err = clBuildProgram(program, 1, &device, 0, 0, 0);


	if (build_err != CL_SUCCESS)
	{
		ft_printf("Opencl build error\n");
		size_t log_size;
    	clGetProgramBuildInfo(program, device, CL_PROGRAM_BUILD_LOG, 0, 0, &log_size);
		char *error_log = ft_malloc(log_size);
		clGetProgramBuildInfo(program, device, CL_PROGRAM_BUILD_LOG, log_size, error_log, 0);
		ft_exit(1);
	}
	ft_printf("Opencl build success\n");

	(void)d;
}
