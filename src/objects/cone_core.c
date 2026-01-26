/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cone_core.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybutkov <ybutkov@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/24 20:44:42 by ybutkov           #+#    #+#             */
/*   Updated: 2026/01/25 22:20:53 by ybutkov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "constants.h"
#include "obj_internal.h"
#include "parser.h"
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

t_obj_type	cone_get_type(void)
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

static t_obj	*create_cone(t_vec3 center, t_vec3 axis,
		float radius_height[2], t_color_reflect color_reflection)
{
	t_obj	*obj;
	t_cone	*cone;

	obj = create_obj(color_reflection.color, color_reflection.reflection,
			DEFAULT_BRIGHTNESS);
	if (obj == NULL)
		return (HANDLE_ERROR_NULL);
	cone = malloc(sizeof(t_cone));
	if (cone == NULL)
		return (free(obj), HANDLE_ERROR_NULL);
	obj->methods = get_cone_methods();
	cone->center = center;
	cone->axis = vector_norm(axis);
	cone->radius = radius_height[0];
	cone->height = radius_height[1];
	cone->slope = cone->radius / cone->height;
	cone->slope_sq = cone->slope * cone->slope;
	cone->m_const = 1.0 + cone->slope_sq;
	obj->data = cone;
	return (obj);
}

// check amount of tokens
int	create_co(t_data_rule rule, char **tokens, t_map *map)
{
	t_vec3			center;
	t_vec3			axis;
	float			radius_height[2];
	t_color_reflect	color_reflection;
	t_obj			*cone;

	(void)rule;
	if (parser_vec3(tokens[1], &center) == NO
		|| parser_vec3(tokens[2], &axis) == NO
		|| get_valid_float(tokens[3], &radius_height[0]) == NO
		|| get_valid_float(tokens[4], &radius_height[1]) == NO
		|| parser_color(tokens[5], &color_reflection.color) == NO)
		return (NO);
	if (get_valid_float(tokens[6], &color_reflection.reflection) != OK)
		color_reflection.reflection = DEFAULT_REFLECTION;
	cone = create_cone(center, axis, radius_height, color_reflection);
	if (cone == NULL)
		return (NO);
	map->add_obj(map, cone);
	return (OK);
}
