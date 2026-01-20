/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_scene.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pberne <pberne@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/20 15:36:43 by pberne            #+#    #+#             */
/*   Updated: 2026/01/20 16:28:56 by pberne           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void	ft_parse_test(char *finename)
{
	int						fd;
	t_testparse_int_v3int	test;
	char					*line;
	t_list					*lst;
	t_parsing_data			*int_node;
	t_parsing_data			*v3i_node;
	char					**strs;

	fd = open(finename, O_RDONLY);
	if (fd == -1)
		return ;
	line = get_next_line_gc(fd);
	lst = 0;
	int_node = ft_malloc_id(sizeof(t_parsing_data), malloc_id_parsing);
	int_node->type = parsing_int;
	v3i_node = ft_malloc_id(sizeof(t_parsing_data), malloc_id_parsing);
	v3i_node->type = parsing_container;
	v3i_node->data_lst = ft_lstnew_gc_id(int_node, malloc_id_parsing);
	ft_lstadd_back(&(v3i_node->data_lst), ft_lstnew_gc_id(int_node,
			malloc_id_parsing));
	ft_lstadd_back(&(v3i_node->data_lst), ft_lstnew_gc_id(int_node,
			malloc_id_parsing));
	ft_lstadd_back(&lst, ft_lstnew_gc_id(int_node, malloc_id_parsing));
	ft_lstadd_back(&lst, ft_lstnew_gc_id(v3i_node, malloc_id_parsing));
	
	while (line)
	{
		ft_str_replace(line, ",\t", ' ');
		strs = ft_split_gc_id(line, ' ', malloc_id_parsing);
		ft_parse_data(strs, &test, lst, 0);
		ft_free(line);
	}
	
}
