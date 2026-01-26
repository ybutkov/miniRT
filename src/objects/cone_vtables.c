/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cone_vtables.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybutkov <ybutkov@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/25 23:22:27 by ybutkov           #+#    #+#             */
/*   Updated: 2026/01/25 23:28:15 by ybutkov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "constants.h"
#include "obj_internal.h"
#include "parser.h"
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

static double	get_cone_height_at_t(t_cone *cone, t_vec3 origin,
	t_vec3 dir, double t)
{
	t_vec3	hit;

	hit = vector_add(origin, vector_mult(dir, t));
	return (vector_dot_product(vector_sub(hit, cone->center), cone->axis));
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

static void	check_cone_solutions(t_cone *cone, t_vec3 origin,
	t_vec3 dir, double t[3])
{
	double	h;

	if (t[0] > EPSILON)
	{
		h = get_cone_height_at_t(cone, origin, dir, t[0]);
		if (h >= -EPSILON && h <= cone->height + EPSILON)
			t[2] = t[0];
	}
	if (t[1] > EPSILON)
	{
		h = get_cone_height_at_t(cone, origin, dir, t[1]);
		if (h >= -EPSILON && h <= cone->height + EPSILON && (t[2] < 0
				|| t[1] < t[2]))
			t[2] = t[1];
	}
}

double	cone_intersect(t_obj *this, t_vec3 origin, t_vec3 dir)
{
	t_cone	*cone;
	t_vec3	oc;
	t_vec3	abc;
	double	t[3];
	double	dv_ov[2];

	cone = (t_cone *)this->data;
	oc = vector_sub(origin, cone->center);
	dv_ov[0] = vector_dot_product(dir, cone->axis);
	dv_ov[1] = vector_dot_product(oc, cone->axis);
	abc.x = dv_ov[0] * dv_ov[0] * cone->m_const - vector_dot_product(dir, dir);
	abc.y = 2.0 * (dv_ov[0] * dv_ov[1] * cone->m_const
			- vector_dot_product(dir, oc));
	abc.z = dv_ov[1] * dv_ov[1] * cone->m_const - vector_dot_product(oc, oc);
	t[2] = -1.0;
	if (solve_quadratic(abc, &t[0], &t[1]) == OK)
		check_cone_solutions(cone, origin, dir, t);
	dv_ov[0] = check_cone_cap(cone, origin, dir);
	if (dv_ov[0] > EPSILON && (t[2] < 0 || dv_ov[0] < t[2]))
		t[2] = dv_ov[0];
	return (t[2]);
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
