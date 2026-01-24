/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder_core.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybutkov <ybutkov@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/06 14:43:38 by ybutkov           #+#    #+#             */
/*   Updated: 2026/01/24 18:36:52 by ybutkov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "constants.h"
#include "obj_internal.h"
#include "parser.h"
#include <math.h>
#include <stdlib.h>

double	pipe_intersect(t_cylinder *cy, t_vec3 origin, t_vec3 dir)
{
	t_vec3	oc;
	double	d_dot;
	double	oc_dot;
	t_vec3	abc;
	double	t[3];

	oc = vector_sub(origin, cy->center);
	d_dot = vector_dot_product(dir, cy->normal);
	oc_dot = vector_dot_product(oc, cy->normal);
	abc.x = vector_dot_product(dir, dir) - d_dot * d_dot;
	abc.y = 2.0 * (vector_dot_product(dir, oc) - d_dot * oc_dot);
	abc.z = vector_dot_product(oc, oc) - oc_dot * oc_dot - cy->radius_sq;
	if (solve_quadratic(abc, &t[0], &t[1]) == NO)
		return (-1.0);
	t[2] = t[0];
	if (t[2] < 0)
		t[2] = t[1];
	if (t[2] < 0)
		return (-1.0);
	return (t[2]);
}

double	check_cap(t_cylinder *cy, t_vec3 origin, t_vec3 dir, t_vec3 cap_center)
{
	t_obj	obj_plane;
	t_plane	plane;
	t_vec3	hit;
	t_vec3	dist_v;
	double	t;

	plane.point = cap_center;
	plane.normal = cy->normal;
	obj_plane.data = &plane;
	t = plane_intersect(&obj_plane, origin, dir);
	if (t > 0)
	{
		hit = vector_add(origin, vector_mult(dir, t));
		dist_v = vector_sub(hit, cap_center);
		if (vector_dot_product(dist_v, dist_v) <= cy->radius_sq)
			return (t);
	}
	return (-1.0);
}

double	cylinder_intersect(t_obj *this, t_vec3 origin, t_vec3 dir)
{
	t_cylinder	*cy;
	t_vec3		temp_vec;
	double		t;
	double		h;
	double		res;

	cy = (t_cylinder *)this->data;
	res = -1.0;
	t = pipe_intersect(cy, origin, dir);
	temp_vec = vector_add(origin, vector_mult(dir, t));
	h = vector_dot_product(vector_sub(temp_vec, cy->center), cy->normal);
	if (t > 0 && h >= -cy->height / 2.0 && h <= cy->height / 2.0)
		res = t;
	temp_vec = vector_mult(cy->normal, cy->height / 2.0);
	t = check_cap(cy, origin, dir, vector_add(cy->center, temp_vec));
	if (t > 0 && (res < 0 || t < res))
		res = t;
	t = check_cap(cy, origin, dir, vector_sub(cy->center, temp_vec));
	if (t > 0 && (res < 0 || t < res))
		res = t;
	return (res);
}

t_aabb	cylinder_get_aabb(t_obj *this)
{
	t_aabb		aabb;
	t_cylinder	*cy;
	t_vec3		half_h;
	t_vec3		top;
	t_vec3		bot;

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

t_obj	*create_cylinder(t_vec3 pos, t_vec3 normal, double diametr_height[2],
		t_color_reflect color_reflection)
{
	t_obj		*obj;
	t_cylinder	*cylinder;

	obj = create_obj(color_reflection.color, color_reflection.reflection,
			DEFAULT_BRIGHTNESS);
	if (obj == NULL)
		return (HANDLE_ERROR_NULL);
	cylinder = malloc(sizeof(t_cylinder));
	if (cylinder == NULL)
		return (free(obj), HANDLE_ERROR_NULL);
	obj->methods = get_cylinder_methods();
	cylinder->center = pos;
	cylinder->normal = vector_norm(normal);
	cylinder->height = diametr_height[1];
	cylinder->radius = diametr_height[0] / 2.0;
	cylinder->radius_sq = diametr_height[0] * diametr_height[0] / 4.0;
	obj->data = cylinder;
	return (obj);
}

int	create_cy(t_data_rule rule, char **tokens, t_map *map)
{
	t_vec3			pos;
	t_vec3			normal;
	double			diametr_height[2];
	t_color_reflect	color_reflection;
	t_obj			*cylinder;

	(void)rule;
	// check amount of tokens
	if (parser_vec3(tokens[1], &pos) == NO ||
		parser_vec3(tokens[2], &normal) == NO ||
		get_valid_float(tokens[3], (float *)&diametr_height[0]) == NO ||
		get_valid_float(tokens[4], (float *)&diametr_height[1]) == NO ||
		parser_color(tokens[5], &color_reflection.color) == NO)
		return (NO);
	if (tokens[6])
	{
		if (get_valid_float(tokens[6],
				(float *)&color_reflection.reflection) == NO)
			return (NO);
	}
	else
		color_reflection.reflection = DEFAULT_REFLECTION;
	cylinder = create_cylinder(pos, normal, diametr_height, color_reflection);
	if (cylinder == NULL)
		return (NO);
	map->add_obj(map, cylinder);
	return (OK);
}
