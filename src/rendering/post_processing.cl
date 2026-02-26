



__kernel void ft_set_and_pack(__global float4 * restrict frame_buff,
	__global float4 * restrict accumulated_buff,
	__global uint * restrict out_packed_buff)
{
	int i = get_global_id(0);
	float4 current = frame_buff[i];

	accumulated_buff[i] = current;
	uchar4 p = convert_uchar4_sat(current * 255.0f);
	out_packed_buff[i] = (p.x << 16) | (p.y << 8) | p.z;
}


__kernel void ft_accumulate_and_pack(__global float4 * restrict frame_buff,
	__global float4 * restrict accumulated_buff,
	__global uint * restrict out_packed_buff,
	const float coef)
{
	int i = get_global_id(0);
	float4 current = frame_buff[i];
	float4 accumulated = accumulated_buff[i];

	accumulated += current;

	accumulated_buff[i] = accumulated;

	float4 final_color = accumulated * coef;
	uchar4 p = convert_uchar4_sat(final_color * 255.0f);
	out_packed_buff[i] = (p.x << 16) | (p.y << 8) | p.z;
}






__kernel void ft_blur_horizontal(__global float4 * restrict src,
	__global float4 * restrict dest,
	const int radius, const int spacing,
	__global const float * restrict gaussian_mat,
	__global const float4 * restrict normal_buff,
	__global const float4 *restrict position_buff,
	const float blur_distance_fallof)
{
	int i = get_global_id(0);
	int j = get_global_id(1);
	int width = get_global_size(0);
	int height = get_global_size(1);

	int x;
	int index = width * j + i;
	float4	normal = normal_buff[index];
	int index_dynamic;
	float4 color = (float4)(0.0f, 0.0f, 0.0f, 0.0f);
	float coef;
	float total_coef = 0;
	float normal_dot;

	float4	center_pos = position_buff[index];
	float4	current_pos;
	float4 	diff;
	for (int k = -radius; k <= radius; k++)
	{
		x = clamp(i + (k * spacing), 0, width - 1);
		index_dynamic = width * j + x;
		coef = gaussian_mat[k + radius];
		float w_n = clamp(dot(normal, normal_buff[index_dynamic]), 0.0f, 1.0f);

		current_pos = position_buff[index_dynamic];
		diff = center_pos - current_pos;
        float dist_sq = dot(diff, diff);
        float w_p = native_exp(-dist_sq * blur_distance_fallof);

		coef = w_n * w_p;
		total_coef += coef;
		color += src[index_dynamic] * coef;
	}
	dest[index] = color / total_coef;
}



__kernel void ft_blur_vertical(__global float4 * restrict src,
	__global float4 * restrict dest,
	const int radius,
	const int spacing,
	__global const float * restrict gaussian_mat,
	__global const float4 * restrict normal_buff,
	__global const float4 * restrict position_buff,
	const float blur_distance_fallof)
{
	int i = get_global_id(0);
	int j = get_global_id(1);
	int width = get_global_size(0);
	int height = get_global_size(1);

	int y;

	int index = width * j + i;
	float4 normal = normal_buff[index];
	int index_dynamic;
	float4 color = (float4)(0.0f, 0.0f, 0.0f, 0.0f);
	float coef;
	float total_coef = 0;

	float4	center_pos = position_buff[index];
	float4	current_pos;
	float4 	diff;
	for (int k = -radius; k <= radius; k++)
	{
		y = clamp(j + (k * spacing), 0, height - 1);
		index_dynamic = width * y + i;
		coef = gaussian_mat[k + radius];
		float w_n = clamp(dot(normal, normal_buff[index_dynamic]), 0.0f, 1.0f);
		current_pos = position_buff[index_dynamic];
		diff = center_pos - current_pos;
        float dist_sq = dot(diff, diff);
        float w_p = native_exp(-dist_sq * blur_distance_fallof);

		coef = w_n * w_p;
		total_coef += coef;
		color += src[index_dynamic] * coef;
	}
	dest[index] = color / total_coef;
}


__kernel void ft_process_normals(__global float4 *normals)
{
	int i = get_global_id(0);

	normals[i] = normals[i] * 0.5f + 0.5f;
}
