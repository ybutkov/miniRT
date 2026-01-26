/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sphere_vtables.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybutkov <ybutkov@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/25 23:33:43 by ybutkov           #+#    #+#             */
/*   Updated: 2026/01/26 20:40:49 by ybutkov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "constants.h"
#include "obj_internal.h"
#include "parser.h"
#include "vectors.h"
#include <stdlib.h>

t_obj_type	sphere_get_type(void)
{
	return (SPHERE);
}

double	sphere_intersect(t_obj *this, t_vec3 origin, t_vec3 dir)
{
	t_sphere	*sphere;
	t_vec3		oc;
	t_vec3		abc;
	double		t[2];

	sphere = (t_sphere *)this->data;
	oc = vector_sub(origin, sphere->center);
	abc.x = vector_dot_product(dir, dir);
	abc.y = 2.0 * vector_dot_product(oc, dir);
	abc.z = vector_dot_product(oc, oc) - sphere->radius_sq;
	if (solve_quadratic(abc, &t[0], &t[1]) == NO)
		return (-1.0);
	if (t[0] > EPSILON)
		return (t[0]);
	if (t[1] > EPSILON)
		return (t[1]);
	return (-1.0);
}

t_aabb	sphere_get_aabb(t_obj *this)
{
	t_aabb		aabb;
	t_sphere	*sphere;

	sphere = (t_sphere *)this->data;
	aabb.min = vector_sub_scalar(sphere->center, sphere->radius);
	aabb.max = vector_add_scalar(sphere->center, sphere->radius);
	return (aabb);
}

t_vec3	sphere_get_normal(t_obj *this, t_vec3 pos)
{
	t_sphere	*sphere;
	t_vec3		normal;

	sphere = (t_sphere *)this->data;
	normal = vector_sub(pos, sphere->center);
	return (vector_norm(normal));
}

t_vtable	*get_sphere_methods(void)
{
	static t_vtable	sphere_methods;
	static int		is_init;

	if (!is_init)
	{
		sphere_methods.get_normal = sphere_get_normal;
		sphere_methods.intersect = sphere_intersect;
		sphere_methods.get_aabb = sphere_get_aabb;
		sphere_methods.get_type = sphere_get_type;
		sphere_methods.get_color = sphere_get_color;
		is_init = 1;
	}
	return (&sphere_methods);
}
