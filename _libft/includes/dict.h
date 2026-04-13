/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dict.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pberne <pberne@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/21 07:46:49 by pberne            #+#    #+#             */
/*   Updated: 2026/01/21 08:10:44 by pberne           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DICT_H
# define DICT_H

# include "libft.h"

typedef struct s_dict
{
	char			*key;
	void			*value;
	struct s_dict	*next;
}					t_dict;

void				ft_dict_set(t_dict **dict, char *key, void *value);
void				*ft_dict_get(t_dict *dict, char *key);
int					ft_dict_try_get(t_dict *dict, char *key, void **out);
void				ft_dict_remove(t_dict **dict, char *key);

#endif