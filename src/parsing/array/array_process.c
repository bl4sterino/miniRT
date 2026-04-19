/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   array_process.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pberne <pberne@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/19 18:44:58 by pberne            #+#    #+#             */
/*   Updated: 2026/04/19 19:22:05 by pberne           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

int ft_try_parse_float(char *buff, size_t *pos, float *out)
{
	float sign = 1.0f;
	float integer = 0.0f;
	float fract = 0.0f;
	while (buff[*pos] == '+' || buff[*pos] == '-')
	{
		if(buff[*pos] == '-')
			sign = -sign;
		*pos += 1;
	}
	if(!ft_try_parse_float_integer(buff, pos, &integer))
		return (1);
	if (buff[*pos] == '.')
	{
		*pos += 1;
		if(!ft_try_parse_float_fract(buff, pos, &fract))
			return (1);
	}
	if(buff[*pos] != '\n' || ft_isspace(buff[*pos]))
		return (1);
	return 	
}


void	ft_try_parse_camera(t_rt_parser_data *data, size_t *pos, t_parsed_object *object)
{
	object->type = object_type_camera;
	*pos += 2;
	while(ft_isspace(data->buffer[*pos]))
		*pos += 1;
	
}

void	ft_process_data(t_rt_parser_data *data)
{
	t_parsed_object	cur;
	size_t			pos;
	size_t			line;

	pos = 0;
	line = 0;
	while (data->buffer[pos])
	{
		if (data->buffer[pos] == '#')
		{
			line++;
			continue ;
		}
		if (ft_strcmp(data->buffer + pos, "C") == 0
			&& ft_isspace(data->buffer[pos + 1]))
			ft_try_parse_camera(data, &pos);
	}
}
