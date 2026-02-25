





__kernel void ft_render_and_pack(__global float4 * restrict frame_buff,
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
	__global const float4 * restrict normal_buff)
{
	int i = get_global_id(0);
	int j = get_global_id(1);
	int width = get_global_size(0);
	int height = get_global_size(1);

	int x;
	int index;

	float4 color = (float4)(0.0f, 0.0f, 0.0f, 0.0f);
	for (int k = -radius; k <= radius; k++)
	{
		x = clamp(i + (k * spacing), 0, width - 1);
		index = width * j + x;
		color += src[index] * gaussian_mat[k + radius];
	}
	dest[width * j + i] = color;
}





__kernel void ft_blur_vertical(__global float4 * restrict src,
	__global float4 * restrict dest,
	const int radius,
	const int spacing,
	__global const float * restrict gaussian_mat,
	__global const float4 * restrict normal_buff)
{
	int i = get_global_id(0);
	int j = get_global_id(1);
	int width = get_global_size(0);
	int height = get_global_size(1);

	int y;
	int index;

	float4 color = (float4)(0.0f, 0.0f, 0.0f, 0.0f);
	for (int k = -radius; k <= radius; k++)
	{
		y = clamp(j + (k * spacing), 0, height - 1);
		index = width * y + i;
		color += src[index] * gaussian_mat[k + radius];
	}
	dest[width * j + i] = color;
}
