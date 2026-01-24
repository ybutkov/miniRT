/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   triangle_core.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybutkov <ybutkov@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/06 21:25:00 by ybutkov           #+#    #+#             */
/*   Updated: 2026/01/24 18:37:10 by ybutkov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "constants.h"
#include "obj_internal.h"
#include "parser.h"
#include <math.h>
#include <stdlib.h>

static double	calc_moller_trumbore(t_vec3 edge[2], t_vec3 origin,
		t_vec3 dir, t_vec3 p1)
{
	t_vec3	h;
	t_vec3	s;
	t_vec3	q;
	double	a;
	double	uv[2];

	h = vector_cross(dir, edge[1]);
	a = vector_dot_product(edge[0], h);
	if (a > -EPSILON && a < EPSILON)
		return (-1.0);
	s = vector_sub(origin, p1);
	uv[0] = vector_dot_product(s, h) / a;
	if (uv[0] < 0.0 || uv[0] > 1.0)
		return (-1.0);
	q = vector_cross(s, edge[0]);
	uv[1] = vector_dot_product(dir, q) / a;
	if (uv[1] < 0.0 || uv[0] + uv[1] > 1.0)
		return (-1.0);
	a = vector_dot_product(edge[1], q) / a;
	if (a > EPSILON)
		return (a);
	return (-1.0);
}

double	triangle_intersect(t_obj *this, t_vec3 origin, t_vec3 dir)
{
	t_triangle	*tri;
	t_vec3		edge[2];

	tri = (t_triangle *)this->data;
	edge[0] = vector_sub(tri->p_2, tri->p_1);
	edge[1] = vector_sub(tri->p_3, tri->p_1);
	return (calc_moller_trumbore(edge, origin, dir, tri->p_1));
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

t_obj	*create_triangle(t_vec3 p_1, t_vec3 p_2, t_vec3 p_3,
		t_color_reflect color_reflection)
{
	t_obj		*obj;
	t_triangle	*triangle;
	t_vec3		normal;

	obj = create_obj(color_reflection.color, color_reflection.reflection,
			DEFAULT_BRIGHTNESS);
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

int	create_tr(t_data_rule rule, char **tokens, t_map *map)
{
	t_vec3			p_1;
	t_vec3			p_2;
	t_vec3			p_3;
	t_color_reflect	color_reflection;
	t_obj			*triangle;

	(void)rule;
	// check amount of tokens
	if (parser_vec3(tokens[1], &p_1) == NO ||
		parser_vec3(tokens[2], &p_2) == NO ||
		parser_vec3(tokens[3], &p_3) == NO ||
		parser_color(tokens[4], &color_reflection.color) == NO)
		return (NO);
	if (tokens[5])
	{
		if (get_valid_float(tokens[5],
				(float *)&color_reflection.reflection) == NO)
			return (NO);
	}
	else
		color_reflection.reflection = DEFAULT_REFLECTION;
	triangle = create_triangle(p_1, p_2, p_3, color_reflection);
	if (triangle == NULL)
		return (NO);
	map->add_obj(map, triangle);
	return (OK);
}
