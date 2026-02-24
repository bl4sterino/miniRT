__kernel void ft_average_data(__global const double *accumulated, __global double *averaged, double coef)
{
	int i = get_global_id(0);
	averaged[i] = min(accumulated[i] * coef, 1.0);
}


__kernel void ft_blur_horizontal(__global double *src, __global double *dest, int radius, int spacing,
	__global const double *gaussian_mat)
{
	int i = get_global_id(0);
	int j = get_global_id(1);
	int width = get_global_size(0);
	int height = get_global_size(1);

	int x;
	int index;

	double color = 0;
	for (int k = -radius; k <= radius; k++)
	{
		x = max(i + (k * spacing) * 3, 0);
		if (x >= width)
			x -= 3;
		index = width * j + x;
		color += src[index] * gaussian_mat[k + radius];
	}
	dest[width * j + i] = color;
}

__kernel void ft_blur_vertical(__global double *src, __global double *dest, int radius, int spacing,
	__global const double *gaussian_mat)
{
	int i = get_global_id(0);
	int j = get_global_id(1);
	int width = get_global_size(0);
	int height = get_global_size(1);

	int y;
	int index;

	double color = 0;
	for (int k = -radius; k <= radius; k++)
	{
		y = clamp(j + (k * spacing), 0, height - 1);
		index = width * y + i;
		color += src[index] * gaussian_mat[k + radius];
	}
	dest[width * j + i] = color;
}
