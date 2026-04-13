/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pberne <pberne@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/01 22:32:24 by pberne            #+#    #+#             */
/*   Updated: 2025/11/09 23:21:40 by pberne           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_empty_str(void)
{
	char	*str;

	str = malloc(1);
	if (str)
		str[0] = '\0';
	return (str);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	long	start;
	long	end;
	long	i;

	i = 0;
	while (s1[i] && ft_strchr(set, s1[i]))
		i++;
	start = i;
	i = ft_strlen(s1) - 1;
	while (i >= 0 && ft_strchr(set, s1[i]))
		i--;
	end = i + 1;
	if (end <= start)
		return (ft_empty_str());
	return (ft_substr(s1, start, end - start));
}
