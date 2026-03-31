/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bvh.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pberne <pberne@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/31 13:52:07 by pberne            #+#    #+#             */
/*   Updated: 2026/03/31 17:55:44 by pberne           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "benchmark.h"
#include "rt.h"
#include <stdio.h>

t_v3f	*ft_get_vectors(unsigned int n)
{
	t_v3f			*vectors;
	unsigned int	i;

	vectors = ft_malloc(sizeof(t_v3f) * n);
	i = 0;
	while (i < n)
	{
		vectors[i] = ft_v3f_random();
		i++;
	}
	return (vectors);
}

void	ft_bench_bvh(t_data *d, unsigned int n)
{
	t_bench_bvh_context	c;

	c.time = ft_get_real_time();
	c.vectors = ft_get_vectors(n);
	c.i = 0;
	c.total = 0;
	c.total_hit = 0;
	c.ray.origin = v3f_a(0.0f);
	while (c.i < n)
	{
		c.ray = ft_setup_ray_direction(c.ray, c.vectors[c.i], 1);
		c.dist = ft_shoot_ray_against_objects(c.ray, FT_INFINITY, d->scene,
				&c.hit);
		if (c.dist < FT_INFINITY)
		{
			c.total += c.dist;
			c.total_hit += c.hit;
		}
		c.i++;
	}
	c.time = ft_get_real_time() - c.time;
	printf("total: %f\ntotalhit:%ld\n time: %f\n", c.total, c.total_hit,
		c.time);
	ft_free(c.vectors);
}

int	main(int ac, char **av)
{
	t_data	d;

	ft_init_data(&d);
	if (ac != 2)
		return (ft_putstr_fd("Wrong number of arguments\n", 2), 0);
	d.mlx = mlx_init();
	if (!d.mlx)
		ft_exit(MALLOC_FAILED);
	d.scene = ft_parse_map(&d, av[1]);
	ft_bench_bvh(&d, 10000000);
	ft_exit(0);
}

// $>./bench_minirt Maps/fibonacci_sphere.rt
// total: 1946238657.707428
// totalhit:1997943510
//  time: 1.816600
// $>./bench_minirt Maps/fibonacci_sphere.rt
// total: 1946238657.707428
// totalhit:1997943510
//  time: 1.813489
// $>./bench_minirt Maps/fibonacci_sphere.rt
// total: 1946238657.707428
// totalhit:1997943510
//  time: 1.813059
// $>./bench_minirt Maps/fibonacci_sphere.rt
// total: 1946238657.707428
// totalhit:1997943510
//  time: 1.812622
