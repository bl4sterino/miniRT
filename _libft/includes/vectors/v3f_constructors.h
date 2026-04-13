/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   v3f_constructors.h                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pberne <pberne@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/30 16:14:21 by pberne            #+#    #+#             */
/*   Updated: 2026/03/30 17:20:04 by pberne           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef V3F_CONSTRUCTORS_H
# define V3F_CONSTRUCTORS_H

# include "vectors.h"

static inline t_v3f	v3f(float x, float y, float z)
{
	return ((t_v3f){{x, y, z, 0.0f}});
}

static inline t_v3f	v3f_a(float a)
{
	return ((t_v3f){{a, a, a, 0.0f}});
}

#endif