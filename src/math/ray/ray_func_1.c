/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_func_1.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybutkov <ybutkov@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/03 21:36:28 by ybutkov           #+#    #+#             */
/*   Updated: 2026/01/16 16:58:28 by ybutkov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "bvh.h"
#include "constants.h"
#include "map.h"
#include "objects.h"
#include "ray_internal.h"
#include "vectors.h"
#include <math.h>
#include <stdlib.h>
#include <unistd.h>

static t_color	add_diffuse_light(t_obj *obj, t_light *light, double dot)
{
	t_color	diff_color;

	diff_color = color_product(obj->color, light->color);
	return (color_mult(diff_color, dot * light->ratio));
}

static t_color	process_light(t_map *map, t_obj *obj, t_vec3 hit_point,
		t_light *light)
{
	t_vec3	light_dir;
	t_vec3	sh_hit_point;
	t_vec3	normal;
	t_vec3	view_dir;
	double	dot;

	normal = obj->methods->get_normal(obj, hit_point);
	view_dir = vector_norm(vector_sub(map->camera->pos, hit_point));
	if (vector_dot_product(normal, view_dir) < 0)
		normal = vector_mult(normal, -1);
	light_dir = vector_norm(vector_sub(light->pos, hit_point));
	dot = vector_dot_product(normal, light_dir);
	sh_hit_point = vector_add(hit_point, vector_mult(normal, 0.01));
	if (dot > 0 && is_in_shadow(map, sh_hit_point, light->pos) == NO)
		return (color_add(add_diffuse_light(obj, light, dot),
				add_specular(light_dir, normal, view_dir, light)));
	return (create_color(0, 0, 0));
}

t_color	calculate_light(t_map *map, t_obj *obj, t_vec3 hit_point)
{
	t_light	*curr;
	t_color	final_color;

	final_color = color_mult(color_product(obj->color, map->ambient->color),
			map->ambient->ratio);
	curr = map->lights;
	while (curr)
	{
		final_color = color_add(final_color, process_light(map, obj, hit_point,
					curr));
		curr = curr->next;
	}
	return (final_color);
}

static t_obj	*get_closest_obj(t_ray ray, t_obj *obj, uint16_t amount_obj,
		double *min_t)
{
	t_obj	*closest_obj;
	double	t;
	double	min;

	min = INFINITY;
	closest_obj = NULL;
	while (amount_obj > 0)
	{
		t = obj->methods->intersect(obj, ray.start, ray.direction);
		if (t > EPSILON && t < min)
		{
			min = t;
			closest_obj = obj;
		}
		obj = obj->next;
		amount_obj--;
	}
	if (min < *min_t)
		*min_t = min;
	return (closest_obj);
}

t_obj	*get_closest_obj_from_bvh(t_ray ray, t_bvh_node *node, double *min_t)
{
	t_obj	*left;
	t_obj	*right;
	t_obj	*result;
	double	t;
	double	left_t;

	if (!node)
		return (NULL);
	t = intersect_aabb(node->aabb, ray.start, ray.direction);
	if (t == -1.0)
		return (NULL);
	if (node->is_leaf == OK)
		return (get_closest_obj(ray, node->obj, node->amount_obj, min_t));
	result = NULL;
	left = get_closest_obj_from_bvh(ray, node->left, min_t);
	left_t = *min_t;
	if (left)
		result = left;
	right = get_closest_obj_from_bvh(ray, node->right, min_t);
	if (right && *min_t < left_t)
		result = right;
	else
		*min_t = left_t;
	return (result);
}
