/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   box_core.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybutkov <ybutkov@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/10 14:02:39 by ybutkov           #+#    #+#             */
/*   Updated: 2026/01/27 14:17:26 by ybutkov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "constants.h"
#include "obj_internal.h"
#include "objects.h"
#include "parser.h"
#include <math.h>
#include <stdlib.h>

static void	calculate_corners(t_box *b, t_vec3 corners[8])
{
	t_vec3	b_0mx[2][3];

	b_0mx[0][0] = vector_mult(b->axis[0], b->half_size.x);
	b_0mx[0][1] = vector_mult(b->axis[1], b->half_size.y);
	b_0mx[0][2] = vector_mult(b->axis[2], b->half_size.z);
	b_0mx[1][0] = vector_mult(b->axis[0], -b->half_size.x);
	b_0mx[1][1] = vector_mult(b->axis[1], -b->half_size.y);
	b_0mx[1][2] = vector_mult(b->axis[2], -b->half_size.z);
	corners[0] = vector_add(b->center,
			vector_add(vector_add(b_0mx[0][0], b_0mx[0][1]), b_0mx[0][2]));
	corners[1] = vector_add(b->center,
			vector_add(vector_add(b_0mx[1][0], b_0mx[0][1]), b_0mx[0][2]));
	corners[2] = vector_add(b->center,
			vector_add(vector_add(b_0mx[0][0], b_0mx[1][1]), b_0mx[0][2]));
	corners[3] = vector_add(b->center,
			vector_add(vector_add(b_0mx[1][0], b_0mx[1][1]), b_0mx[0][2]));
	corners[4] = vector_add(b->center,
			vector_add(vector_add(b_0mx[0][0], b_0mx[0][1]), b_0mx[1][2]));
	corners[5] = vector_add(b->center,
			vector_add(vector_add(b_0mx[1][0], b_0mx[0][1]), b_0mx[1][2]));
	corners[6] = vector_add(b->center,
			vector_add(vector_add(b_0mx[0][0], b_0mx[1][1]), b_0mx[1][2]));
	corners[7] = vector_add(b->center,
			vector_add(vector_add(b_0mx[1][0], b_0mx[1][1]), b_0mx[1][2]));
}

t_aabb	box_get_aabb(t_obj *this)
{
	t_aabb	aabb;
	t_box	*box;
	t_vec3	corners[8];
	int		i;

	aabb = get_empty_aabb();
	box = (t_box *)this->data;
	calculate_corners(box, corners);
	aabb.min = corners[0];
	aabb.max = corners[0];
	i = 1;
	while (i < 8)
	{
		aabb.min.x = fmin(aabb.min.x, corners[i].x);
		aabb.min.y = fmin(aabb.min.y, corners[i].y);
		aabb.min.z = fmin(aabb.min.z, corners[i].z);
		aabb.max.x = fmax(aabb.max.x, corners[i].x);
		aabb.max.y = fmax(aabb.max.y, corners[i].y);
		aabb.max.z = fmax(aabb.max.z, corners[i].z);
		i++;
	}
	return (aabb);
}

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

static t_obj	*create_box(t_vec3 center, t_vec3 orientation, t_vec3 size,
		t_color_reflect color_reflection)
{
	t_obj	*obj;
	t_box	*box;
	t_vec3	up;

	obj = create_obj(color_reflection.color, color_reflection.reflection,
			DEFAULT_BRIGHTNESS);
	if (obj == NULL)
		return (HANDLE_ERROR_NULL);
	box = malloc(sizeof(t_box));
	if (box == NULL)
		return (free(obj), HANDLE_ERROR_NULL);
	obj->methods = get_box_methods();
	box->center = center;
	box->half_size = create_vector(size.x * 0.5, size.y * 0.5, size.z * 0.5);
	box->axis[2] = vector_norm(orientation);
	if (fabs(box->axis[2].y) < 0.9)
		up = create_vector(0, 1, 0);
	else
		up = create_vector(0, 0, 1);
	box->axis[0] = vector_norm(vector_cross(up, box->axis[2]));
	box->axis[1] = vector_cross(box->axis[2], box->axis[0]);
	obj->data = box;
	return (obj);
}

// check amount of tokens
int	create_b(t_data_rule rule, char **tokens, t_map *map)
{
	t_vec3			center;
	t_vec3			orientation;
	t_vec3			size;
	t_color_reflect	color_reflection;
	t_obj			*box;

	(void)rule;
	if (parser_vec3(tokens[1], &center) == NO
		|| parser_vec3(tokens[2], &orientation) == NO
		|| parser_vec3(tokens[3], &size) == NO
		|| parser_color(tokens[4], &color_reflection.color) == NO)
		return (NO);
	if (get_valid_float(tokens[5], &color_reflection.reflection) != OK)
		color_reflection.reflection = DEFAULT_REFLECTION;
	box = create_box(center, orientation, size, color_reflection);
	if (box == NULL)
		return (NO);
	map->add_obj(map, box);
	return (OK);
}
