/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putstr_batch.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pberne <pberne@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/25 14:41:12 by pberne            #+#    #+#             */
/*   Updated: 2025/11/25 14:58:47 by pberne           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

void	ft_putstr_batch(int fd, ...)
{
	va_list	ap;
	char	*str;

	va_start(ap, fd);
	str = va_arg(ap, char *);
	while (str[0])
	{
		ft_putstr_fd(str, fd);
		str = va_arg(ap, char *);
	}
}

int	ft_putstr_batch_ret(int fd, int ret, ...)
{
	va_list	ap;
	char	*str;

	va_start(ap, ret);
	str = va_arg(ap, char *);
	while (str[0])
	{
		ft_putstr_fd(str, fd);
		str = va_arg(ap, char *);
	}
	return (ret);
}
