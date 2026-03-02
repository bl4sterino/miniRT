/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   collisions_inlined.h                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pberne <pberne@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/28 20:18:09 by pberne            #+#    #+#             */
/*   Updated: 2026/03/02 21:42:24 by pberne           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COLLISIONS_INLINED_H
# define COLLISIONS_INLINED_H

# include "rt.h"

static inline float	ft_bounds_collision(t_ray ray, t_bounds b)
{
	t_v2f	min_max;
	float	t1;
	float	t2;

	min_max.x = (b.v[ray.inv_sign[0]].x - ray.origin.x) * ray.inv_dir.x;
	min_max.y = (b.v[1 - ray.inv_sign[0]].x - ray.origin.x) * ray.inv_dir.x;
	if (min_max.x > min_max.y)
		return (INFINITY);
	t1 = (b.v[ray.inv_sign[1]].y - ray.origin.y) * ray.inv_dir.y;
	t2 = (b.v[1 - ray.inv_sign[1]].y - ray.origin.y) * ray.inv_dir.y;
	if (t1 > min_max.x)
		min_max.x = t1;
	if (t2 < min_max.y)
		min_max.y = t2;
	if (min_max.x > min_max.y)
		return (INFINITY);
	t1 = (b.v[ray.inv_sign[2]].z - ray.origin.z) * ray.inv_dir.z;
	t2 = (b.v[1 - ray.inv_sign[2]].z - ray.origin.z) * ray.inv_dir.z;
	if (t1 > min_max.x)
		min_max.x = t1;
	if (t2 < min_max.y)
		min_max.y = t2;
	if (min_max.x > min_max.y || min_max.y < 0.0f)
		return (INFINITY);
	return (tn_f(min_max.x > 0.0f, min_max.x, 0.0f));
}

#include <immintrin.h>
static inline void ft_intersect_aabb_x2_fast(
    __m128 r_org[3], __m128 r_inv[3], 
    const t_bounds *b1, const t_bounds *b2, 
    float *dist1, float *dist2)
{
    // Use _mm_setr_ps to load min/max for both boxes into one register
    __m128 b_min_x = _mm_setr_ps(b1->min.x, b2->min.x, 0, 0);
    __m128 b_max_x = _mm_setr_ps(b1->max.x, b2->max.x, 0, 0);
    __m128 b_min_y = _mm_setr_ps(b1->min.y, b2->min.y, 0, 0);
    __m128 b_max_y = _mm_setr_ps(b1->max.y, b2->max.y, 0, 0);
    __m128 b_min_z = _mm_setr_ps(b1->min.z, b2->min.z, 0, 0);
    __m128 b_max_z = _mm_setr_ps(b1->max.z, b2->max.z, 0, 0);

    // Slab algorithm
    __m128 t1 = _mm_mul_ps(_mm_sub_ps(b_min_x, r_org[0]), r_inv[0]);
    __m128 t2 = _mm_mul_ps(_mm_sub_ps(b_max_x, r_org[0]), r_inv[0]);
    __m128 tmin = _mm_min_ps(t1, t2);
    __m128 tmax = _mm_max_ps(t1, t2);

    t1 = _mm_mul_ps(_mm_sub_ps(b_min_y, r_org[1]), r_inv[1]);
    t2 = _mm_mul_ps(_mm_sub_ps(b_max_y, r_org[1]), r_inv[1]);
    tmin = _mm_max_ps(tmin, _mm_min_ps(t1, t2));
    tmax = _mm_min_ps(tmax, _mm_max_ps(t1, t2));

    t1 = _mm_mul_ps(_mm_sub_ps(b_min_z, r_org[2]), r_inv[2]);
    t2 = _mm_mul_ps(_mm_sub_ps(b_max_z, r_org[2]), r_inv[2]);
    tmin = _mm_max_ps(tmin, _mm_min_ps(t1, t2));
    tmax = _mm_min_ps(tmax, _mm_max_ps(t1, t2));

    // Extraction (Aligning to 16-byte boundary for safety)
    float res_min[4] __attribute__((aligned(16)));
    float res_max[4] __attribute__((aligned(16)));
    _mm_store_ps(res_min, tmin);
    _mm_store_ps(res_max, tmax);

    // Results with validity check
    *dist1 = (res_min[0] <= res_max[0] && res_max[0] > 0.0f) ? res_min[0] : INFINITY;
    *dist2 = (res_min[1] <= res_max[1] && res_max[1] > 0.0f) ? res_min[1] : INFINITY;
}

static inline float	ft_sphere_collision(t_ray ray, t_sphere sphere)
{
	t_v3f	oc;
	float	a;
	float	b;
	float	discriminant;
	float	t;
	float	sqrt_d;

	oc = ft_v3f_sub(ray.origin, sphere.position);
	a = ft_v3f_dot(ray.direction, ray.direction);
	b = 2.0f * ft_v3f_dot(ray.direction, oc);
	discriminant = (b * b) - (4.0f * a * (ft_v3f_dot(oc, oc) - (sphere.radius
					* sphere.radius)));
	if (discriminant < 0.0f)
		return (INFINITY);
	sqrt_d = sqrtf(discriminant);
	t = (-b - sqrt_d) / (2.0f * a);
	if (t < EPSILON)
		t = (-b + sqrt_d) / (2.0f * a);
	if (t < EPSILON)
		return (INFINITY);
	return (t);
}

static inline float	ft_plane_collision(t_ray ray, t_plane plane)
{
	float	denom;
	float	t;
	t_v3f	oc;

	denom = ft_v3f_dot(plane.normal, ray.direction);
	if (fabsf(denom) < EPSILON)
		return (INFINITY);
	oc = ft_v3f_sub(plane.position, ray.origin);
	t = ft_v3f_dot(oc, plane.normal) / denom;
	if (t < 0.0f)
		return (INFINITY);
	return (t);
}

/* This one is Gemini's, didin't look into it but it just works™  */
static inline float	ft_cylinder_collision(t_ray ray, t_cylinder cyl)
{
	t_v3f	oc;
	t_v3f	q;
	float	t_hit;
	float	half_h;

	float a, b, c, disc, t0, t1, h, r;
	r = cyl.diameter * 0.5f;
	oc = ft_v3f_sub(ray.origin, cyl.position);
	a = 1.0f - powf(ft_v3f_dot(ray.direction, cyl.normal), 2.0f);
	b = 2.0f * (ft_v3f_dot(ray.direction, oc) - (ft_v3f_dot(ray.direction,
					cyl.normal) * ft_v3f_dot(oc, cyl.normal)));
	c = ft_v3f_dot(oc, oc) - powf(ft_v3f_dot(oc, cyl.normal), 2.0f) - (r * r);
	disc = (b * b) - (4 * a * c);
	if (disc < 0)
		return (INFINITY);
	t0 = (-b - sqrtf(disc)) / (2.0f * a);
	t1 = (-b + sqrtf(disc)) / (2.0f * a);
	t_hit = INFINITY;
	half_h = cyl.height * 0.5f;
	if (t0 > 0.0f)
	{
		q = ft_v3f_add(ray.origin, ft_v3f_scale(ray.direction, t0));
		h = ft_v3f_dot(ft_v3f_sub(q, cyl.position), cyl.normal);
		if (h >= -half_h && h <= half_h)
			t_hit = t0;
	}
	if (t_hit == INFINITY && t1 > 0.0f)
	{
		q = ft_v3f_add(ray.origin, ft_v3f_scale(ray.direction, t1));
		h = ft_v3f_dot(ft_v3f_sub(q, cyl.position), cyl.normal);
		if (h >= -half_h && h <= half_h)
			t_hit = t1;
	}
	return (t_hit);
}

static inline float	ft_quad_collision(t_ray ray, t_quad quad)
{
	t_v3f	oc;
	float	denom;
	float	t;
	t_v3f	hit_p;
	t_v3f	planar_pos;
	float	u;
	float	v;

	denom = ft_v3f_dot(quad.normal, ray.direction);
	if (fabsf(denom) < EPSILON)
		return (INFINITY);
	oc = ft_v3f_sub(quad.position, ray.origin);
	t = ft_v3f_dot(oc, quad.normal) / denom;
	if (t < EPSILON)
		return (INFINITY);
	hit_p = ft_v3f_add(ray.origin, ft_v3f_scale(ray.direction, t));
	planar_pos = ft_v3f_sub(hit_p, quad.position);
	u = ft_v3f_dot(planar_pos, quad.u_axis);
	v = ft_v3f_dot(planar_pos, quad.v_axis);
	if (fabsf(u) > quad.size.x * 0.5f || fabsf(v) > quad.size.y * 0.5f)
		return (INFINITY);
	return (t);
}

static inline float	ft_triangle_collision(t_ray ray, t_triangle tri)
{
	t_v3f	edge1;
	t_v3f	edge2;
	t_v3f	h;
	t_v3f	s;
	t_v3f	q;
	float	det;
	float	inv_det;
	float	u;
	float	v;
	float	t;

	edge1 = ft_v3f_sub(tri.points.b, tri.points.a);
	edge2 = ft_v3f_sub(tri.points.c, tri.points.a);
	h = ft_v3f_cross(ray.direction, edge2);
	det = ft_v3f_dot(edge1, h);
	// If determinant is near zero, ray is parallel to the triangle
	if (det > -EPSILON && det < EPSILON)
		return (INFINITY);
	inv_det = 1.0f / det;
	s = ft_v3f_sub(ray.origin, tri.points.a);
	u = inv_det * ft_v3f_dot(s, h);
	// Check if intersection lies outside the triangle
	if (u < 0.0f || u > 1.0f)
		return (INFINITY);
	q = ft_v3f_cross(s, edge1);
	v = inv_det * ft_v3f_dot(ray.direction, q);
	if (v < 0.0f || u + v > 1.0f)
		return (INFINITY);
	// Calculate t to see where the intersection point is on the line
	t = inv_det * ft_v3f_dot(edge2, q);
	if (t >= EPSILON)
		return (t);
	return (INFINITY);
}

#endif
