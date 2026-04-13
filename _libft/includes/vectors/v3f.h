/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   v3f.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pberne <pberne@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/19 14:45:52 by pberne            #+#    #+#             */
/*   Updated: 2026/03/06 14:36:37 by pberne           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef V3F_H
# define V3F_H

typedef float	t_v4sf	__attribute__((vector_size(16)));
typedef int		t_v4si		__attribute__((vector_size(16)));

typedef union u_v3f
{
	t_v4sf				v;
	struct
	{
		float			x;
		float			y;
		float			z;
		float			w;
	};
} __attribute__((aligned(16)))	t_v3f;

static inline t_v3f	ft_v3f_add(const t_v3f a, const t_v3f b)
{
	return ((t_v3f){a.v + b.v});
}

static inline t_v3f	ft_v3f_sub(const t_v3f a, const t_v3f b)
{
	return ((t_v3f){a.v - b.v});
}

static inline t_v3f	ft_v3f_mult(t_v3f a, t_v3f b)
{
	return ((t_v3f){a.v * b.v});
}

static inline t_v3f	ft_v3f_scale(t_v3f a, float d)
{
	return ((t_v3f){a.v * d});
}

static inline t_v3f	ft_v3f_div(t_v3f a, float d)
{
	return ((t_v3f){a.v * (1.0f / d)});
}

#endif
