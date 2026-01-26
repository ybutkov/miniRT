/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   plane_core.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybutkov <ybutkov@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/05 21:43:49 by ybutkov           #+#    #+#             */
/*   Updated: 2026/01/25 23:29:26 by ybutkov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "constants.h"
#include "obj_internal.h"
#include "parser.h"
#include <math.h>
#include <stdlib.h>

double	plane_intersect(t_obj *this, t_vec3 origin, t_vec3 dir)
{
	t_plane	*plane;
	t_vec3	p0_l0;
	double	denom;
	double	t;

	plane = (t_plane *)this->data;
	denom = vector_dot_product(plane->normal, dir);
	if (fabs(denom) > EPSILON)
	{
		p0_l0 = vector_sub(plane->point, origin);
		t = vector_dot_product(p0_l0, plane->normal) / denom;
		if (t >= 0)
			return (t);
	}
	return (-1.0);
}

t_aabb	plane_get_aabb(t_obj *this)
{
	t_aabb	aabb;

	(void)this;
	aabb.min = create_vector(-INFINITY, -INFINITY, -INFINITY);
	aabb.max = create_vector(INFINITY, INFINITY, INFINITY);
	return (aabb);
}

static t_obj	*create_plane(t_vec3 point, t_vec3 normal, t_color color,
		float reflection)
{
	t_obj	*obj;
	t_plane	*plane;

	obj = create_obj(color, reflection, DEFAULT_BRIGHTNESS);
	if (obj == NULL)
		return (HANDLE_ERROR_NULL);
	plane = malloc(sizeof(t_plane));
	if (plane == NULL)
		return (free(obj), HANDLE_ERROR_NULL);
	obj->methods = get_plane_methods();
	plane->point = point;
	plane->normal = normal;
	obj->data = plane;
	return (obj);
}

// check amount of tokens
int	create_pl(t_data_rule rule, char **tokens, t_map *map)
{
	t_vec3			point;
	t_vec3			normal;
	t_color_reflect	color_reflection;
	t_obj			*plane;

	(void)rule;
	if (parser_vec3(tokens[1], &point) == NO
		|| parser_vec3(tokens[2], &normal) == NO
		|| parser_color(tokens[3], &color_reflection.color) == NO)
		return (NO);
	if (get_valid_float(tokens[4], &color_reflection.reflection) != OK)
		color_reflection.reflection = DEFAULT_REFLECTION;
	plane = create_plane(point, normal, color_reflection.color,
			color_reflection.reflection);
	if (plane == NULL)
		return (NO);
	map->add_obj(map, plane);
	return (OK);
}
