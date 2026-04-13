/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isspace.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pberne <pberne@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/16 09:52:19 by pberne            #+#    #+#             */
/*   Updated: 2026/01/16 09:52:21 by pberne           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	ft_isspace(int c)
{
	if ((c >= 9 && c <= 13) || c == 32)
		return (1);
	return (0);
}

/// @brief returns the first index containing a space, or -1 if none
/// @param str
/// @return
int	ft_get_next_space_index(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (ft_isspace(str[i]))
			break ;
		i++;
	}
	if (!str[i])
		i = -1;
	return (i);
}
