/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pberne <pberne@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/23 10:33:58 by pberne            #+#    #+#             */
/*   Updated: 2025/11/30 16:44:44 by pberne           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_print_string_count(char *str)
{
	if (!str)
		return (write(1, "(null)", 1));
	return (ft_putstr_fd_count(str, 1));
}

void	ft_print_until_flag(char *str, int *i, int *count)
{
	char	c;
	int		start;
	int		total;

	start = *i;
	c = str[*i];
	while (c != '\0' && c != '%')
	{
		*i += 1;
		c = str[*i];
	}
	total = *i - start;
	if (total > 0)
		*count += write(1, str + start, total);
}

void	ft_print_valid_flag(char *str, va_list ap, int *i, int *count)
{
	if (str[*i] == '%')
		*count += write(1, "%", 1);
	else if (str[*i] == 's')
		*count += ft_print_string_count(va_arg(ap, char *));
	else if (str[*i] == 'd')
		*count += ft_putnbr_base_l(va_arg(ap, int), "0123456789");
	else if (str[*i] == 'x')
		*count += ft_putnbr_base_l(va_arg(ap, int), "0123456789abcdef");
	else if (str[*i] == 'l')
		*count += ft_putnbr_base_l(va_arg(ap, long), "0123456789");
	else if (str[*i] == 'c')
		*count += ft_putchar_ret(va_arg(ap, int));
	else if (str[*i] == 'p')
	{
		*count += write(1, "0x", 2);
		*count += ft_putnbr_base_ul(va_arg(ap, unsigned long),
				"0123456789abcdef");
	}
	else if (str[*i] == 'f')
		*count += ft_putdouble(va_arg(ap, double));
}

void	ft_print_flag(char *str, va_list ap, int *i, int *count)
{
	*i += 1;
	if (ft_strchr("%sdxlcpf", str[*i]))
		ft_print_valid_flag(str, ap, i, count);
	else
	{
		*count += write(1, "%", 1);
		if (str[*i] != '\0')
			*count += write(1, str + *i, 1);
	}
	if (str[*i] != '\0')
		*i += 1;
}

int	ft_printf(char *str, ...)
{
	va_list	ap;
	int		count;
	int		i;

	i = 0;
	count = 0;
	va_start(ap, str);
	while (str[i])
	{
		ft_print_until_flag(str, &i, &count);
		if (str[i] == '%')
			ft_print_flag(str, ap, &i, &count);
	}
	return (count);
}
