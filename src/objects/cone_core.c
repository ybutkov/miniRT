/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cone_core.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybutkov <ybutkov@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/24 20:44:42 by ybutkov           #+#    #+#             */
/*   Updated: 2026/01/24 23:33:43 by ybutkov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "constants.h"
#include "obj_internal.h"
#include "parser.h"
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

t_obj	*create_cone(t_vec3 center, t_vec3 axis, double radius_height[2],
		t_color_reflect color_reflection)
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

int	create_co(t_data_rule rule, char **tokens, t_map *map)
{
	t_vec3			center;
	t_vec3			axis;
	float			temp[2];
	double			radius_height[2];
	t_color_reflect	color_reflection;
	t_obj			*cone;

	(void)rule;
	// check amount of tokens
	if (parser_vec3(tokens[1], &center) == NO ||
		parser_vec3(tokens[2], &axis) == NO ||
		get_valid_float(tokens[3], &temp[0]) == NO ||
		get_valid_float(tokens[4], &temp[1]) == NO ||
		parser_color(tokens[5], &color_reflection.color) == NO)
		return (NO);
	radius_height[0] = (double)temp[0];
	radius_height[1] = (double)temp[1];
	if (tokens[6])
	{
		if (get_valid_float(tokens[6],
				(float *)&color_reflection.reflection) == NO)
			return (NO);
	}
	else
		color_reflection.reflection = DEFAULT_REFLECTION;
	cone = create_cone(center, axis, radius_height, color_reflection);
	if (cone == NULL)
		return (NO);
	map->add_obj(map, cone);
	return (OK);
}
