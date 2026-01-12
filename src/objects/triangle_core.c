/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   triangle_core.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybutkov <ybutkov@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/06 21:25:00 by ybutkov           #+#    #+#             */
/*   Updated: 2026/01/12 20:40:17 by ybutkov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "constants.h"
#include "objects.h"
#include <math.h>
#include <stdlib.h>

t_obj_type	triangle_get_type(void)
{
	return (TRIANGLE);
}

double	triangle_intersect(t_obj *this, t_vec3 origin, t_vec3 dir)
{
	t_triangle	*triangle;
	t_vec3		edge_1;
	t_vec3		edge_2;
	t_vec3		s;
	t_vec3		h;
	t_vec3		q;
	double		a;
	double		u;
	double		v;
	double		t;

	triangle = (t_triangle *)this->data;
	edge_1 = vector_sub(triangle->p_2, triangle->p_1);
	edge_2 = vector_sub(triangle->p_3, triangle->p_1);
	h = vector_cross(dir, edge_2);
	a = vector_dot_product(edge_1, h);
	if (a > -EPSILON && a < EPSILON)
		return (-1.0);
	s = vector_sub(origin, triangle->p_1);
	u = vector_dot_product(s, h) * 1.0 / a;
	if (u < 0.0 || u > 1.0)
		return (-1.0);
	q = vector_cross(s, edge_1);
	v = vector_dot_product(dir, q) * 1.0 / a;
	if (v < 0.0 || u + v > 1.0)
		return (-1.0);
	t = vector_dot_product(edge_2, q) * 1.0 / a;
	if (t > EPSILON)
		return (t);
	return (-1.0);
}

t_vec3	triangle_get_normal(t_obj *this, t_vec3 pos)
{
	t_triangle	*triangle;

	(void)pos;
	triangle = (t_triangle *)this->data;
	return (triangle->normal);
}

t_aabb	triangle_get_aabb(t_obj *this)
{
	t_aabb		aabb;
	t_triangle	*triangle;

	triangle = (t_triangle *)this->data;
	aabb.min.x = fmin(fmin(triangle->p_1.x, triangle->p_2.x), triangle->p_3.x);
	aabb.min.y = fmin(fmin(triangle->p_1.y, triangle->p_2.y), triangle->p_3.y);
	aabb.min.z = fmin(fmin(triangle->p_1.z, triangle->p_2.z), triangle->p_3.z);
	aabb.max.x = fmax(fmax(triangle->p_1.x, triangle->p_2.x), triangle->p_3.x);
	aabb.max.y = fmax(fmax(triangle->p_1.y, triangle->p_2.y), triangle->p_3.y);
	aabb.max.z = fmax(fmax(triangle->p_1.z, triangle->p_2.z), triangle->p_3.z);
	return (aabb);
}

t_vtable	*get_triangle_methods(void)
{
	static t_vtable	triangle_methods;
	static int		is_init;

	if (!is_init)
	{
		triangle_methods.get_normal = triangle_get_normal;
		triangle_methods.intersect = triangle_intersect;
		triangle_methods.get_aabb = triangle_get_aabb;
		triangle_methods.get_type = triangle_get_type;
		is_init = 1;
	}
	return (&triangle_methods);
}

t_obj	*create_triangle(t_vec3 p_1, t_vec3 p_2, t_vec3 p_3, t_color color, double reflection)
{
	t_obj		*obj;
	t_triangle	*triangle;
	t_vec3		normal;

	obj = create_obj(color, reflection, DEFAULT_BRIGHTNESS);
	if (obj == NULL)
		return (HANDLE_ERROR_NULL);
	triangle = malloc(sizeof(t_triangle));
	if (triangle == NULL)
		return (free(obj), HANDLE_ERROR_NULL);
	obj->methods = get_triangle_methods();
	triangle->p_1 = p_1;
	triangle->p_2 = p_2;
	triangle->p_3 = p_3;
	normal = vector_norm(vector_cross(vector_sub(p_2, p_1),
				vector_sub(p_3, p_1)));
	triangle->normal = normal;
	obj->data = triangle;
	return (obj);
}
