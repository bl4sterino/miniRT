/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pberne <pberne@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/20 11:19:43 by pberne            #+#    #+#             */
/*   Updated: 2026/02/19 11:51:56 by pberne           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_try_or_default(t_parsing_data *parsing_node, void *dest)
{
	if (parsing_node->type == p_double_try_or_0)
	{
		*((double *)dest) = 0.0;
		return (1);
	}
	else if (parsing_node->type == p_float_try_or_0)
	{
		*((float *)dest) = 0.0f;
		return (1);
	}
	return (0);
}

int	ft_parse_node_2(char *arg, char *dest, t_parsing_data *parsing_node)
{
	if (parsing_node->type == p_float
		|| parsing_node->type == p_float_try_or_0)
		return (ft_atof_safe(arg, (float *)dest));
	else if (parsing_node->type == p_float_0_255_to_0_1)
		return (ft_atof_safe_0_255_to_0_1(arg, (float *)dest));
	else if (parsing_node->type == p_float_0_1)
		return (ft_atof_safe_0_1(arg, (float *)dest));
	return (0);
}

/// @brief ft_parse_node uses the appropriate function to parse the line  data,
/// and then advances the line data pointer to the next element of a line.
///
/// the parsing methods are advancing the dest pointer based on the size of the
/// element they are parsing
/// @param malloc_id
int	ft_parse_node(t_parse_context context, t_parsing_data *parsing_node,
		int base_offset)
{
	char	*arg;
	char	*dest;

	dest = context.start;
	dest += base_offset + parsing_node->offset;
	arg = **context.line_data;
	*context.line_data += 1;
	if (!arg)
		return (ft_try_or_default(parsing_node, (void *)dest));
	if (parsing_node->type == p_uchar)
		return (ft_atouc_safe(arg, (unsigned char *)dest));
	else if (parsing_node->type == p_int)
		return (ft_atoi_safe(arg, (int *)dest));
	else if (parsing_node->type == p_double
		|| parsing_node->type == p_double_try_or_0)
		return (ft_atod_safe(arg, (double *)dest));
	else if (parsing_node->type == p_double_0_255_to_0_1)
		return (ft_atod_safe_0_255_to_0_1(arg, (double *)dest));
	else if (parsing_node->type == p_double_0_1)
		return (ft_atod_safe_0_1(arg, (double *)dest));
	else if (parsing_node->type == p_string)
		return (ft_parse_string(arg, (char **)dest, context.malloc_id));
	else
		return (ft_parse_node_2(arg, dest, parsing_node));
}

int	ft_parse_data_r(t_parse_context context, int base_offset)
{
	t_parsing_data	*node_data;
	int				i;

	i = 0;
	while (context.line_format)
	{
		node_data = context.line_format->content;
		if (!ft_parse_node(context, node_data, base_offset))
			return (0);
		context.line_format = context.line_format->next;
		i++;
	}
	return (i);
}

/// @brief Parse the line based on the types defines by line_format
/// @param line_data points to a char[][] obtained by a split, every char[]
/// contains a value that needs parsing.
/// @param line_format
/// @param malloc_id
int	ft_parse_data(char **line_data, void *dest, t_list *line_format,
		int malloc_id)
{
	t_parse_context	context;

	if (!line_format || !dest || !line_data)
		return (0);
	context.line_data = &line_data;
	context.start = dest;
	context.malloc_id = malloc_id;
	context.line_format = line_format;
	return (ft_parse_data_r(context, 0));
}
