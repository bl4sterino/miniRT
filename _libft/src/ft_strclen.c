/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strclen.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pberne <pberne@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/16 10:23:56 by pberne            #+#    #+#             */
/*   Updated: 2026/01/16 10:23:57 by pberne           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
** @brief Returns the lengths of a string up to c,
**	or to the end if c is not found
** @param str A string
** @param c ASCII character
** @return The length of the string up to c
*/
int	ft_strclen(const char *str, char c)
{
	int	len;

	len = 0;
	while (str[len] && str[len] != c)
		len++;
	return (len);
}
