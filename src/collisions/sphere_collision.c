/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sphere_collision.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pberne <pberne@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/23 11:20:37 by pberne            #+#    #+#             */
/*   Updated: 2026/01/23 11:56:49 by pberne           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

double	ft_sphere_collision(t_ray ray, t_sphere sphere)
{
	t_v3d	oc;
	double	a;
	double	b;
	double	c;
	double	discriminant;

	oc = ft_v3d_sub(ray.origin, sphere.position);
	
	a = ft_v3d_dot(ray.direction, ray.direction);
	b = 2.0 * ft_v3d_dot(ray.direction, oc);
	c = ft_v3d_dot(oc, oc) - (sphere.radius * sphere.radius);
	
	discriminant = (b * b) - (4 * a * c);

	if (discriminant < 0)
		return (-1.0);
	double t = (-b - sqrt(discriminant)) / (2.0 * a);
	
	if (t < 0)
		t = (-b + sqrt(discriminant)) / (2.0 * a);
	
	if (t < 0)
		return (-1.0);

	return (t);
}
