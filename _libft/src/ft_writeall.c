/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_writeall.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpotier <tpotier@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/27 17:15:38 by tpotier           #+#    #+#             */
/*   Updated: 2026/02/27 17:29:18 by tpotier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>

#include "libft.h"

ssize_t	ft_write_all(int fd, const void *data, size_t len)
{
	ssize_t	ret;
	size_t	written;

	written = 0;
	while (written < len)
	{
		ret = write(fd, &((uint8_t *)data)[written], len - written);
		if (ret < 0)
			return (ret);
		written += ret;
	}
	return (len);
}
