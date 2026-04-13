/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putstr_fd_ret.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pberne <pberne@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/14 15:37:30 by pberne            #+#    #+#             */
/*   Updated: 2025/12/07 16:03:44 by pberne           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/// @brief Prints s to fd and returns ret
int	ft_putstr_fd_ret(char *s, int fd, int ret)
{
	ft_putstr_fd(s, fd);
	return (ret);
}
