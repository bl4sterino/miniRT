/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scene_data.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pberne <pberne@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/20 15:31:29 by pberne            #+#    #+#             */
/*   Updated: 2026/01/21 08:13:54 by pberne           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SCENE_DATA_H
# define SCENE_DATA_H

# include "rt.h"

typedef struct s_testparse_int_v3int
{
	int		int_value;
	t_v3i	vector_int;
	double	double_value;
}			t_testparse_int_v3int;

#endif