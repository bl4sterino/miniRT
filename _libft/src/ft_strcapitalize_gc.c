/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcapitalize_gc.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pberne <pberne@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/16 10:23:45 by pberne            #+#    #+#             */
/*   Updated: 2026/01/16 11:46:54 by pberne           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_str_to_lower_gc(char *str)
{
	return (ft_str_to_lower_gc_id(str, 0));
}

char	*ft_str_to_upper_gc(char *str)
{
	return (ft_str_to_upper_gc_id(str, 0));
}

char	*ft_str_to_lower_gc_id(char *str, int id)
{
	char	*dest;
	size_t	i;

	i = -1;
	if (!str)
		return (NULL);
	dest = ft_malloc_id(ft_strlen(str) + 1, id);
	while (str[++i])
		dest[i] = ft_tolower(str[i]);
	return (dest);
}

char	*ft_str_to_upper_gc_id(char *str, int id)
{
	char	*dest;
	size_t	i;

	i = -1;
	if (!str)
		return (NULL);
	dest = ft_malloc_id(ft_strlen(str) + 1, id);
	while (str[++i])
		dest[i] = ft_toupper(str[i]);
	return (dest);
}
