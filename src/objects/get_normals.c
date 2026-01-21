/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_normals.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybutkov <ybutkov@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/15 15:52:15 by ybutkov           #+#    #+#             */
/*   Updated: 2026/01/15 21:52:40 by ybutkov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "obj_internal.h"
#include "constants.h"
#include <math.h>

t_vec3	box_get_normal(t_obj *this, t_vec3 pos)
{
	t_box				*box;
	t_box_normal_utils	b_vars;
	int					i;

	box = (t_box *)this->data;
	b_vars.d = vector_sub(pos, box->center);
	b_vars.min_dist = INFINITY;
	b_vars.axis = 0;
	i = 0;
	while (i < 3)
	{
		b_vars.points[i] = vector_dot_product(b_vars.d, box->axis[i]);
		b_vars.dist = fabs(box->half_size.v[i] - fabs(b_vars.points[i]));
		if (b_vars.dist < b_vars.min_dist)
		{
			b_vars.min_dist = b_vars.dist;
			b_vars.axis = i;
		}
		i++;
	}
	if (b_vars.points[b_vars.axis] > 0)
		return (box->axis[b_vars.axis]);
	return (vector_mult(box->axis[b_vars.axis], -1));
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

t_vec3	plane_get_normal(t_obj *this, t_vec3 pos)
{
	t_plane	*plane;

	(void)pos;
	plane = (t_plane *)this->data;
	return (vector_norm(plane->normal));
}

t_vec3	sphere_get_normal(t_obj *this, t_vec3 pos)
{
	t_sphere	*sphere;
	t_vec3		normal;

	sphere = (t_sphere *)this->data;
	normal = vector_sub(pos, sphere->center);
	return (vector_norm(normal));
}

t_vec3	triangle_get_normal(t_obj *this, t_vec3 pos)
{
	t_triangle	*triangle;

	(void)pos;
	triangle = (t_triangle *)this->data;
	return (triangle->normal);
}
