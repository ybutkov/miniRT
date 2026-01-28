/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder_vtables.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybutkov <ybutkov@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/06 14:43:38 by ybutkov           #+#    #+#             */
/*   Updated: 2026/01/27 14:17:26 by ybutkov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "constants.h"
#include "obj_internal.h"
#include "parser.h"
#include <math.h>
#include <stdlib.h>

t_obj_type	cylinder_get_type(void)
{
	return (CYLINDER);
}

t_aabb	cylinder_get_aabb(t_obj *this)
{
	t_aabb		aabb;
	t_cylinder	*cy;
	t_vec3		half_h;
	t_vec3		top;
	t_vec3		bot;

	aabb = get_empty_aabb();
	cy = (t_cylinder *)this->data;
	half_h = vector_mult(cy->normal, cy->height / 2.0);
	top = vector_add(cy->center, half_h);
	bot = vector_sub(cy->center, half_h);
	aabb.min.x = fmin(top.x, bot.x) - cy->radius;
	aabb.min.y = fmin(top.y, bot.y) - cy->radius;
	aabb.min.z = fmin(top.z, bot.z) - cy->radius;
	aabb.max.x = fmax(top.x, bot.x) + cy->radius;
	aabb.max.y = fmax(top.y, bot.y) + cy->radius;
	aabb.max.z = fmax(top.z, bot.z) + cy->radius;
	return (aabb);
}

t_vec3	cylinder_get_normal(t_obj *this, t_vec3 pos)
{
	t_cylinder	*cylinder;
	t_vec3		v;
	t_vec3		pr;
	double		h;

	cylinder = (t_cylinder *)this->data;
	v = vector_sub(pos, cylinder->center);
	h = vector_dot_product(v, cylinder->normal);
	if (h > (cylinder->height / 2.0 - EPSILON))
		return (cylinder->normal);
	if (h < (-cylinder->height / 2.0 + EPSILON))
		return (vector_mult(cylinder->normal, -1));
	pr = vector_mult(cylinder->normal, h);
	return (vector_norm(vector_sub(v, pr)));
}

t_vtable	*get_cylinder_methods(void)
{
	static t_vtable	cylinder_methods;
	static int		is_init;

	if (!is_init)
	{
		cylinder_methods.get_normal = cylinder_get_normal;
		cylinder_methods.intersect = cylinder_intersect;
		cylinder_methods.get_aabb = cylinder_get_aabb;
		cylinder_methods.get_type = cylinder_get_type;
		cylinder_methods.get_color = default_get_color;
		is_init = 1;
	}
	return (&cylinder_methods);
}
