/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atof.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pberne <pberne@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/06 01:23:17 by pberne            #+#    #+#             */
/*   Updated: 2026/02/27 14:56:51 by pberne           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_atof_data_init(t_atof_data *d)
{
	d->divider = 10.0;
	d->is_decimal = 0;
	d->nb = 0.0;
	d->i = 0;
	d->sign = 1.0;
}

void	ft_skip_space_sign(t_atof_data *d, char *str)
{
	while (str[d->i] == ' ')
		d->i += 1;
	while (str[d->i] == '-' || str[d->i] == '+')
	{
		if (str[d->i] == '-')
			d->sign *= -1.0f;
		d->i += 1;
	}
}

float	ft_atof(char *str)
{
	t_atof_data	d;

	ft_atof_data_init(&d);
	ft_skip_space_sign(&d, str);
	while (ft_strchr(".0123456789", str[d.i]))
	{
		if (str[d.i] == '.')
			d.is_decimal = 1;
		else if (!d.is_decimal)
		{
			d.nb *= 10.0f;
			d.nb += (double)(str[d.i] - '0');
		}
		else
		{
			d.nb += (double)(str[d.i] - '0') / d.divider;
			d.divider *= 10.0f;
		}
		d.i += 1;
	}
	return ((float)(d.nb * d.sign));
}

double	ft_atod(char *str)
{
	t_atof_data	d;

	ft_atof_data_init(&d);
	ft_skip_space_sign(&d, str);
	while (ft_strchr(".0123456789", str[d.i]))
	{
		if (str[d.i] == '.')
			d.is_decimal = 1;
		else if (!d.is_decimal)
		{
			d.nb *= 10.0f;
			d.nb += (double)(str[d.i] - '0');
		}
		else
		{
			d.nb += (double)(str[d.i] - '0') / d.divider;
			d.divider *= 10.0f;
		}
		d.i += 1;
	}
	return ((d.nb * d.sign));
}

int	ft_atod_safe(char *str, double *dest)
{
	t_atof_data	d;

	*dest = 0.0;
	ft_atof_data_init(&d);
	ft_skip_space_sign(&d, str);
	while (ft_strchr(".0123456789", str[d.i]))
	{
		if (str[d.i] == '.')
			d.is_decimal = 1;
		else if (!d.is_decimal)
		{
			d.nb *= 10.0f;
			d.nb += (double)(str[d.i] - '0');
		}
		else
		{
			d.nb += (double)(str[d.i] - '0') / d.divider;
			d.divider *= 10.0f;
		}
		d.i += 1;
	}
	if (str[d.i] != '\0')
		return (0);
	*dest = d.nb * d.sign;
	return (1);
}
