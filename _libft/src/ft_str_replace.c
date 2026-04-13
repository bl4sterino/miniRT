/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_str_replace.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pberne <pberne@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/20 11:48:56 by pberne            #+#    #+#             */
/*   Updated: 2026/01/20 11:57:46 by pberne           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_str_replace(char *src, char *charset, char replacement)
{
	int	i;

	i = 0;
	while (src[i])
	{
		if (ft_strchr(charset, src[i]))
			src[i] = replacement;
		i++;
	}
}
