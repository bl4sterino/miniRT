/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   opencl_errors.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pberne <pberne@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/25 21:57:10 by pberne            #+#    #+#             */
/*   Updated: 2026/03/01 17:35:26 by pberne           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

#ifndef OPENCL_BONK

const char	*get_cl_error_3(cl_int error)
{
	if (error == CL_INVALID_WORK_GROUP_SIZE)
		return ("CL_INVALID_WORK_GROUP_SIZE");
	else if (error == CL_INVALID_WORK_ITEM_SIZE)
		return ("CL_INVALID_WORK_ITEM_SIZE");
	else if (error == CL_INVALID_GLOBAL_OFFSET)
		return ("CL_INVALID_GLOBAL_OFFSET");
	else if (error == CL_EXEC_STATUS_ERROR_FOR_EVENTS_IN_WAIT_LIST)
		return ("CL_EXEC_STATUS_ERROR_FOR_EVENTS_IN_WAIT_LIST");
	else if (error == CL_INVALID_MEM_OBJECT)
		return ("CL_INVALID_MEM_OBJECT");
	else if (error == CL_INVALID_COMMAND_QUEUE)
		return ("CL_INVALID_COMMAND_QUEUE");
	else if (error == CL_INVALID_BINARY)
		return ("CL_INVALID_BINARY");
	else if (error == CL_INVALID_SAMPLER)
		return ("CL_INVALID_SAMPLER");
	else if (error == CL_INVALID_IMAGE_SIZE)
		return ("CL_INVALID_IMAGE_SIZE");
	else if (error == CL_INVALID_IMAGE_FORMAT_DESCRIPTOR)
		return ("CL_INVALID_IMAGE_FORMAT_DESCRIPTOR");
	return ("UNKNOWN_OPENCL_ERROR");
}

const char	*get_cl_error_2(cl_int error)
{
	if (error == CL_LINKER_NOT_AVAILABLE)
		return ("CL_LINKER_NOT_AVAILABLE");
	else if (error == CL_LINK_PROGRAM_FAILURE)
		return ("CL_LINK_PROGRAM_FAILURE");
	else if (error == CL_INVALID_PROGRAM_EXECUTABLE)
		return ("CL_INVALID_PROGRAM_EXECUTABLE");
	else if (error == CL_INVALID_VALUE)
		return ("CL_INVALID_VALUE");
	else if (error == CL_INVALID_CONTEXT)
		return ("CL_INVALID_CONTEXT");
	else if (error == CL_INVALID_KERNEL_NAME)
		return ("CL_INVALID_KERNEL_NAME");
	else if (error == CL_INVALID_KERNEL_DEFINITION)
		return ("CL_INVALID_KERNEL_DEFINITION");
	else if (error == CL_INVALID_KERNEL)
		return ("CL_INVALID_KERNEL");
	else if (error == CL_INVALID_ARG_INDEX)
		return ("CL_INVALID_ARG_INDEX");
	else if (error == CL_INVALID_ARG_VALUE)
		return ("CL_INVALID_ARG_VALUE");
	else if (error == CL_INVALID_ARG_SIZE)
		return ("CL_INVALID_ARG_SIZE");
	else if (error == CL_INVALID_KERNEL_ARGS)
		return ("CL_INVALID_KERNEL_ARGS");
	return (get_cl_error_3(error));
}

const char	*get_cl_error(cl_int error)
{
	if (error == CL_SUCCESS)
		return ("CL_SUCCESS");
	else if (error == CL_DEVICE_NOT_FOUND)
		return ("CL_DEVICE_NOT_FOUND");
	else if (error == CL_DEVICE_NOT_AVAILABLE)
		return ("CL_DEVICE_NOT_AVAILABLE");
	else if (error == CL_COMPILER_NOT_AVAILABLE)
		return ("CL_COMPILER_NOT_AVAILABLE");
	else if (error == CL_DEVICE_PARTITION_FAILED)
		return ("CL_DEVICE_PARTITION_FAILED");
	else if (error == CL_MEM_OBJECT_ALLOCATION_FAILURE)
		return ("CL_MEM_OBJECT_ALLOCATION_FAILURE");
	else if (error == CL_OUT_OF_RESOURCES)
		return ("CL_OUT_OF_RESOURCES");
	else if (error == CL_OUT_OF_HOST_MEMORY)
		return ("CL_OUT_OF_HOST_MEMORY");
	else if (error == CL_MAP_FAILURE)
		return ("CL_MAP_FAILURE");
	else if (error == CL_BUILD_PROGRAM_FAILURE)
		return ("CL_BUILD_PROGRAM_FAILURE");
	else if (error == CL_COMPILE_PROGRAM_FAILURE)
		return ("CL_COMPILE_PROGRAM_FAILURE");
	return (get_cl_error_2(error));
}

#endif
