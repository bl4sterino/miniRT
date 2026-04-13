/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putstr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pberne <pberne@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/02 16:37:27 by pberne            #+#    #+#             */
/*   Updated: 2025/12/07 16:08:23 by pberne           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putstr_fd(char *s, int fd)
{
	size_t	len;
	size_t	written;
	ssize_t	write_ret;
	size_t	remaining;

	len = ft_strlen(s);
	written = 0;
	write_ret = 0;
	remaining = len;
	while (written < len)
	{
		write_ret = write(fd, s + written, remaining);
		if (write_ret < 0)
			return ;
		remaining -= written;
		written += write_ret;
	}
}
