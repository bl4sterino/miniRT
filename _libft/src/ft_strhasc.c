/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strhasc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pberne <pberne@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/01 18:03:06 by lomartin          #+#    #+#             */
/*   Updated: 2026/01/14 13:03:16 by pberne           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	ft_str_has_only_c(char *str, char c)
{
	while (*str)
	{
		if (*str != c)
			return (0);
		str++;
	}
	return (1);
}

int	ft_strhasc(const char *str, char c)
{
	while (*str)
	{
		if (*str == c)
			return (1);
		++str;
	}
	return (0);
}
