/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_error.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pberne <pberne@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/22 10:57:18 by pberne            #+#    #+#             */
/*   Updated: 2026/01/22 11:48:35 by pberne           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void	ft_parsing_error_on_line(int n)
{
	char	*str;

	str = ft_strjoin_mult_gc_id(0, 3, "Parsing error at line: ", ft_itoa_gc(n),
			"\n");
	ft_putstr_fd(str, 2);
	ft_exit(EXIT_FAILURE);
}
