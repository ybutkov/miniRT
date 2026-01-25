/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cone_vtables.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybutkov <ybutkov@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/24 20:59:22 by ybutkov           #+#    #+#             */
/*   Updated: 2026/01/25 15:27:43 by ybutkov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "constants.h"
#include "obj_internal.h"
#include "parser.h"
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

static t_obj_type	cone_get_type(void)
{
	return (CONE);
}

t_vec3	cone_get_normal(t_obj *this, t_vec3 pos)
{
	t_vec3	normal;
	t_cone	*cone;
	t_vec3	cp;
	double	dist;
	t_vec3	projection;

	cone = (t_cone *)this->data;
	cp = vector_sub(pos, cone->center);
	dist = vector_dot_product(cp, cone->axis);
	projection = vector_mult(cone->axis, dist);
	normal = vector_sub(cp, vector_mult(projection, 1.0 + cone->slope_sq));
	return (vector_norm(normal));
}

static double	check_cone_cap(t_cone *cone, t_vec3 origin, t_vec3 dir)
{
	t_vec3	cap_center;
	t_vec3	hit;
	t_vec3	dist_v;
	double	denom;
	double	t;

	cap_center = vector_add(cone->center, vector_mult(cone->axis,
				cone->height));
	denom = vector_dot_product(cone->axis, dir);
	if (fabs(denom) < EPSILON)
		return (-1.0);
	t = vector_dot_product(vector_sub(cap_center, origin), cone->axis) / denom;
	if (t <= EPSILON)
		return (-1.0);
	hit = vector_add(origin, vector_mult(dir, t));
	dist_v = vector_sub(hit, cap_center);
	if (vector_dot_product(dist_v, dist_v) <= cone->radius * cone->radius)
		return (t);
	return (-1.0);
}

double	cone_intersect(t_obj *this, t_vec3 origin, t_vec3 dir)
{
	t_cone	*cone;
	t_vec3	oc;
	t_vec3	abc;
	double	dv;
	double	ov;
	double	dvdv;
	double	ococ;
	double	dvoc;
	double	k;
	double	t[3];
	double	h;

	cone = (t_cone *)this->data;
	oc = vector_sub(origin, cone->center);
	dv = vector_dot_product(dir, cone->axis);
	ov = vector_dot_product(oc, cone->axis);
	dvdv = vector_dot_product(dir, dir);
	ococ = vector_dot_product(oc, oc);
	dvoc = vector_dot_product(dir, oc);
	k = cone->slope_sq;
	abc.x = dv * dv * cone->m_const - dvdv;
	abc.y = 2.0 * (dv * ov * cone->m_const - dvoc);
	abc.z = ov * ov * cone->m_const - ococ;
	t[2] = -1.0;
	if (solve_quadratic(abc, &t[0], &t[1]) == OK)
	{
		if (t[0] > EPSILON)
		{
			h = vector_dot_product(vector_sub(vector_add(origin,
							vector_mult(dir, t[0])), cone->center), cone->axis);
			if (h >= -EPSILON && h <= cone->height + EPSILON)
				t[2] = t[0];
		}
		if (t[1] > EPSILON)
		{
			h = vector_dot_product(vector_sub(vector_add(origin,
							vector_mult(dir, t[1])), cone->center), cone->axis);
			if (h >= -EPSILON && h <= cone->height + EPSILON && (t[2] < 0
					|| t[1] < t[2]))
				t[2] = t[1];
		}
	}
	h = check_cone_cap(cone, origin, dir);
	if (h > EPSILON && (t[2] < 0 || h < t[2]))
		t[2] = h;
	return (t[2]);
}

t_aabb	cone_get_aabb(t_obj *this)
{
	t_aabb	aabb;
	t_cone	*cone;
	t_vec3	apex;
	t_vec3	base_center;
	double	max_radius;

	cone = (t_cone *)this->data;
	apex = cone->center;
	base_center = vector_add(cone->center, vector_mult(cone->axis,
				cone->height));
	max_radius = cone->radius;
	aabb.min.x = fmin(apex.x - max_radius, base_center.x - max_radius);
	aabb.min.y = fmin(apex.y - max_radius, base_center.y - max_radius);
	aabb.min.z = fmin(apex.z - max_radius, base_center.z - max_radius);
	aabb.max.x = fmax(apex.x + max_radius, base_center.x + max_radius);
	aabb.max.y = fmax(apex.y + max_radius, base_center.y + max_radius);
	aabb.max.z = fmax(apex.z + max_radius, base_center.z + max_radius);
	return (aabb);
}

t_vtable	*get_cone_methods(void)
{
	static t_vtable	cone_methods;
	static int		is_init;

	if (!is_init)
	{
		cone_methods.get_normal = cone_get_normal;
		cone_methods.intersect = cone_intersect;
		cone_methods.get_aabb = cone_get_aabb;
		cone_methods.get_type = cone_get_type;
		cone_methods.get_color = default_get_color;
		is_init = 1;
	}
	return (&cone_methods);
}
