/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_data_dict.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pberne <pberne@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/21 10:26:09 by pberne            #+#    #+#             */
/*   Updated: 2026/01/28 10:09:37 by pberne           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

t_parsing_data	*ft_get_pdata(int malloc_id, t_parsing_data d)
{
	t_parsing_data	*data;

	data = ft_malloc_id(sizeof(t_parsing_data), malloc_id);
	data->type = d.type;
	data->offset = d.offset;
	data->data_lst = 0;
	return (data);
}

t_dict	*ft_setup_parsing_dict(t_dict *dict, int malloc_id)
{
	ft_dict_set(&dict, "A", ft_get_parser_ambient_light(malloc_id));
	ft_dict_set(&dict, "C", ft_get_parser_camera(malloc_id));
	ft_dict_set(&dict, "L", ft_get_parser_light(malloc_id));
	ft_dict_set(&dict, "sp", ft_get_parser_sphere(malloc_id));
	ft_dict_set(&dict, "pl", ft_get_parser_plane(malloc_id));
	ft_dict_set(&dict, "cy", ft_get_parser_cylinder(malloc_id));
	return (dict);
}
