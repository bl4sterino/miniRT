/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pberne <pberne@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/20 11:24:58 by pberne            #+#    #+#             */
/*   Updated: 2026/02/19 10:54:35 by pberne           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

# include "libft.h"

typedef enum e_parsing_type
{
	p_char,
	p_uchar,
	p_int,
	p_uint,
	p_long,
	p_ulong,
	p_float,
	p_float_0_1,
	p_float_0_255_to_0_1,
	p_float_try_or_0,
	p_double,
	p_double_0_1,
	p_double_0_255_to_0_1,
	p_double_try_or_0,
	p_string
}					t_parsing_type;

typedef struct s_parse_context
{
	int				malloc_id;
	void			*start;
	char			***line_data;
	t_list			*line_format;
}					t_parse_context;

/// @brief data_lst is used for the container type, it encapsulates
/// sub types for teh content of a struct or an array
typedef struct s_parsing_data
{
	t_parsing_type	type;
	int				offset;
	t_list			*data_lst;
}					t_parsing_data;

int					ft_parse_data(char **line_data, void *dest,
						t_list *line_format, int malloc_id);

int					ft_parse_string(char *arg, char **dest, int malloc_id);

#endif