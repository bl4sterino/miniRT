/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pberne <pberne@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/31 16:44:19 by pberne            #+#    #+#             */
/*   Updated: 2025/11/08 10:00:49 by pberne           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

char	*ft_strrchr(const char *str, int c)
{
	int		i;
	int		latest;
	char	*out;
	char	cc;

	cc = (char)c;
	latest = -1;
	i = 0;
	out = 0;
	while (str[i])
	{
		if (str[i] == cc)
			latest = i;
		i++;
	}
	if (str[i] == c)
		latest = i;
	if (latest != -1)
		out = (char *)str + latest;
	return (out);
}
