/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_type.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pberne <pberne@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/20 15:00:26 by pberne            #+#    #+#             */
/*   Updated: 2026/01/21 15:34:25 by pberne           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_parse_string(char *arg, char **dest, int malloc_id)
{
	if (!arg)
		return (0);
	*dest = ft_strdup_gc_id(arg, malloc_id);
	return (1);
}
