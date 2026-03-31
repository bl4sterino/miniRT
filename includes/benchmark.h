/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   benchmark.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pberne <pberne@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/31 16:40:34 by pberne            #+#    #+#             */
/*   Updated: 2026/03/31 17:15:47 by pberne           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BENCHMARK_H
# define BENCHMARK_H

# include "rt.h"

typedef struct s_bench_bvh_context
{
	t_v3f			*vectors;
	unsigned int	i;
	double			time;
	double			total;
	float			dist;
	t_ray			ray;
	int				hit;
	long			total_hit;
}					t_bench_bvh_context;

#endif