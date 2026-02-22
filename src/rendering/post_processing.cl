__kernel void ft_average_data(__global const double *accumulated, __global float *averaged, double coef)
{
	int i = get_global_id(0);
	averaged[i] = accumulated[i] * coef;
}
