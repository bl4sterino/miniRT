
__kernel void ft_accumulate(__global float4 *frame, __global float4 *accumulated_frames, __private const float coef)
{
	int i = get_global_id(0);
 
	accumulated_frames[i] += frame[i];
	frame[i] =  accumulated_frames[i] * coef;
}

__kernel void ft_blur_horizontal(__global float4 *src, __global float4 *dest, const int radius, const int spacing,
	__global const float *gaussian_mat, __global const float4 *normals)
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

__kernel void ft_blur_vertical(__global float4 *src, __global float4 *dest, const int radius, const int spacing,
	__global const float *gaussian_mat, __global const float4 *normals)
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
