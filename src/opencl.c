/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   opencl.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pberne <pberne@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/22 22:05:51 by pberne            #+#    #+#             */
/*   Updated: 2026/02/23 11:52:28 by pberne           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

const char *get_cl_error(cl_int error)
{
    switch(error)
    {
        // Segmentation/Initialization Errors
        case 0: return "CL_SUCCESS";
        case -1: return "CL_DEVICE_NOT_FOUND";
        case -2: return "CL_DEVICE_NOT_AVAILABLE";
        case -3: return "CL_COMPILER_NOT_AVAILABLE";
        case -4: return "CL_MEM_OBJECT_ALLOCATION_FAILURE";
        case -5: return "CL_OUT_OF_RESOURCES";
        case -6: return "CL_OUT_OF_HOST_MEMORY";
        
        // Argument/Kernel Errors
        case -30: return "CL_INVALID_VALUE";
        case -34: return "CL_INVALID_CONTEXT";
        case -36: return "CL_INVALID_COMMAND_QUEUE";
        case -38: return "CL_INVALID_MEM_OBJECT";
        case -48: return "CL_INVALID_KERNEL";
        case -52: return "CL_INVALID_KERNEL_ARGS";
        case -54: return "CL_INVALID_WORK_GROUP_SIZE";
        
        // Program/Build Errors
        case -11: return "CL_BUILD_PROGRAM_FAILURE";
        case -42: return "CL_INVALID_BINARY";
        
        default: return "UNKNOWN_OPENCL_ERROR";
    }
}

void	ft_init_opencl(t_data *d)
{
	cl_uint			num_platforms;
	cl_platform_id	*platforms;

	clGetPlatformIDs(0, NULL, &num_platforms);
	platforms = ft_malloc(sizeof(cl_platform_id) * num_platforms);
	clGetPlatformIDs(num_platforms, platforms, NULL);
	d->opencl.platform = platforms[0];

	cl_uint num_devices;
	clGetDeviceIDs(d->opencl.platform, CL_DEVICE_TYPE_GPU, 0, NULL, &num_devices);
	cl_device_id devices[num_devices];
	clGetDeviceIDs(d->opencl.platform, CL_DEVICE_TYPE_GPU, num_devices, devices, NULL);
	d->opencl.device = devices[0];


	char *prg_str = ft_read_file_gc_id("src/rendering/post_processing.cl", 0);
	if(!prg_str)
		ft_exit_str_fd(1, "Failed to load OpenCl kernel source\n", 2);
	int err;

	d->opencl.context = clCreateContext(0, 1, &d->opencl.device, 0, 0, &err);
	ft_printf("Created context, err: %d\n", err);
	
	cl_program program = clCreateProgramWithSource(d->opencl.context, 1, &prg_str, 0, &err);
	ft_printf("Created program, err: %d\n", err);

	cl_int build_err = clBuildProgram(program, 1, &d->opencl.device, 0, 0, 0);


	if (build_err != CL_SUCCESS)
	{
		ft_printf("Opencl build error\n");
		size_t log_size;
    	clGetProgramBuildInfo(program, d->opencl.device, CL_PROGRAM_BUILD_LOG, 0, 0, &log_size);
		char *error_log = ft_malloc(log_size);
		clGetProgramBuildInfo(program, d->opencl.device, CL_PROGRAM_BUILD_LOG, log_size, error_log, 0);
		ft_exit(1);
	}
	ft_printf("Opencl build success\n");

	d->opencl.kernel_average = clCreateKernel(program, "ft_average_data", 0);

	d->opencl.accumulated_buff = clCreateBuffer(d->opencl.context, CL_MEM_READ_WRITE, HEIGHT_WIN * WIDTH_WIN * 3 * sizeof(double), 0, &err);
	ft_printf("Created accumulated buffer, err: %d\n", err);
	d->opencl.averaged_buff = clCreateBuffer(d->opencl.context, CL_MEM_READ_WRITE, HEIGHT_WIN * WIDTH_WIN * 3 * sizeof(double), 0, &err);
	ft_printf("Created averaged buffer, err: %d\n", err);

	err = clSetKernelArg(d->opencl.kernel_average, 0, sizeof(cl_mem), &d->opencl.accumulated_buff);
	if (err != CL_SUCCESS)
		ft_printf("Error Setting kernel arg 0: %s\n", get_cl_error(err));


	err = clSetKernelArg(d->opencl.kernel_average, 1, sizeof(cl_mem), &d->opencl.averaged_buff);
	if (err != CL_SUCCESS)
		ft_printf("Error Setting kernel arg 1: %s\n", get_cl_error(err));

	d->opencl.command_queue = clCreateCommandQueue(d->opencl.context, d->opencl.device, 0, &err);
	ft_printf("Created queue, err: %d\n", err);
}
