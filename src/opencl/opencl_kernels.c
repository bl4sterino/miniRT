/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   opencl_kernels.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pberne <pberne@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/25 22:03:37 by pberne            #+#    #+#             */
/*   Updated: 2026/02/25 23:09:17 by pberne           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void ft_create_blur_kernels(t_data *d)
{
	cl_int	err;

	d->opencl.kernel_blur_h = clCreateKernel(d->opencl.program,
			"ft_blur_horizontal", &err);
	if (err != CL_SUCCESS)
	{
		ft_printf("Error Creating H_blur kernel: %s\n", get_cl_error(err));
		ft_exit(1);
	}
	d->opencl.kernel_blur_v = clCreateKernel(d->opencl.program,
			"ft_blur_vertical", &err);
	if (err != CL_SUCCESS)
	{
		ft_printf("Error Creating V_blur kernel: %s\n", get_cl_error(err));
		ft_exit(1);
	}
	err += clSetKernelArg(d->opencl.kernel_blur_h, 5, sizeof(cl_mem),
			&d->opencl.normals_buff);
	err += clSetKernelArg(d->opencl.kernel_blur_v, 5, sizeof(cl_mem),
			&d->opencl.normals_buff);
	if (err != CL_SUCCESS)
	{
		ft_printf("Error Setting blur kernel arg: %s\n", get_cl_error(err));
		ft_exit(1);
	}
}

void ft_create_render_and_pack_kernel(t_data *d)
{
	cl_int err;
	d->opencl.kernel_render_and_pack = clCreateKernel(d->opencl.program,
			"ft_render_and_pack", &err);
	if (err != CL_SUCCESS)
	{
		ft_printf("Error Creating H_blur kernel: %s\n", get_cl_error(err));
		ft_exit(1);
	}
	err += clSetKernelArg(d->opencl.kernel_render_and_pack, 0, sizeof(cl_mem),
			&d->opencl.frame_buff);
	err += clSetKernelArg(d->opencl.kernel_render_and_pack, 1, sizeof(cl_mem),
			&d->opencl.accumulated_buff);
	err += clSetKernelArg(d->opencl.kernel_render_and_pack, 2, sizeof(cl_mem),
			&d->opencl.out_packed_buff);
	
}

void	ft_create_kernels(t_data *d)
{
	ft_create_blur_kernels(d);
	ft_create_render_and_pack_kernel(d);
}
