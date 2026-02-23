__kernel void ft_average_data(__global const double *accumulated, __global double *averaged, double coef)
{
	int i = get_global_id(0);
	averaged[i] = min(accumulated[i] * coef, 1.0);
}
