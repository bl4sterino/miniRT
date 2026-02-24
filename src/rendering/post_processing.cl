__kernel void ft_average_data(__global const double *accumulated, __global double *averaged, double coef)
{
	int max = get_global_id(0) * 32 + 32;
	for (int i = get_global_id(0) * 32; i < max; i++)
	{
		averaged[i] = min(accumulated[i] * coef, 1.0);
	}
}


__kernel void ft_blur(__global double *src, __global double *dest)
{
	int i = get_global_id(0);
	int j = get_global_id(1);
	int width = get_global_size(0);
	int height = get_global_size(1);

	int index = (width * j) + i;

	double color = 0;
	for (int y = j - 2; y <= j + 2; y++)
	{
		int yy = clamp(y, 0, height);
		for (int x = i - 6; x <= i + 6; x += 3)
		{
			color += src[width * yy + clamp(x, 0, 1280*720*3)];
		}
	}
	dest[index] = color / 25.0;
}
