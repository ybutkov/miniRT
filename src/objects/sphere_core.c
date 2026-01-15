/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sphere_core.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybutkov <ybutkov@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/04 17:49:55 by ybutkov           #+#    #+#             */
/*   Updated: 2026/01/15 21:33:06 by ybutkov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "constants.h"
#include "obj_internal.h"
#include "vectors.h"
#include <stdlib.h>

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

t_obj	*create_sphere(t_vec3 pos, double diametr, t_color color,
		double reflection)
{
	t_obj		*obj;
	t_sphere	*sphere;

	obj = create_obj(color, reflection, DEFAULT_BRIGHTNESS);
	if (obj == NULL)
		return (HANDLE_ERROR_NULL);
	sphere = malloc(sizeof(t_sphere));
	if (sphere == NULL)
		return (free(obj), HANDLE_ERROR_NULL);
	obj->methods = get_sphere_methods();
	sphere->center = pos;
	sphere->radius = diametr / 2.0;
	sphere->radius_sq = diametr * diametr / 4.0;
	obj->data = sphere;
	return (obj);
}
