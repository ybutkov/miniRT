/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_core.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybutkov <ybutkov@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/03 21:36:28 by ybutkov           #+#    #+#             */
/*   Updated: 2026/01/16 16:11:44 by ybutkov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "bvh.h"
#include "constants.h"
#include "map.h"
#include "objects.h"
#include "rays.h"
#include "vectors.h"
#include <math.h>
#include <stdlib.h>
#include <unistd.h>

t_ray	create_ray(t_vec3 start, t_vec3 direction)
{
	t_ray	ray;

	ray.start = start;
	ray.direction = vector_norm(direction);
	return (ray);
}

t_vec3	ray_at_pos(t_ray ray, double pos)
{
	return (vector_add(ray.start, vector_mult(ray.direction, pos)));
}

t_ray	get_ray(t_camera *cam, double x_ratio, double y_ratio)
{
	t_vec3	target;
	t_vec3	direction;

	target = vector_add(cam->lower_left_pos,
			vector_add(vector_mult(cam->horizontal, x_ratio),
				vector_mult(cam->vertical, y_ratio)));
	direction = vector_sub(target, cam->pos);
	return (create_ray(cam->pos, direction));
}

int	is_in_shadow_bvh(t_bvh_node *node, t_vec3 origin, t_vec3 dir,
		double max_dist)
{
	t_obj		*obj;
	double		t;
	uint16_t	amount;

	if (!node || intersect_aabb(node->aabb, origin, dir) == -1.0)
		return (NO);
	if (node->is_leaf == OK)
	{
		obj = node->obj;
		amount = node->amount_obj;
		while (amount > 0)
		{
			t = obj->methods->intersect(obj, origin, dir);
			if (t > EPSILON && t < max_dist)
				return (OK);
			obj = obj->next;
			amount--;
		}
		return (NO);
	}
	if (node->left && is_in_shadow_bvh(node->left, origin, dir, max_dist))
		return (OK);
	if (node->right && is_in_shadow_bvh(node->right, origin, dir, max_dist))
		return (OK);
	return (NO);
}

int	is_in_shadow(t_map *map, t_vec3 hit_point, t_vec3 light_pos)
{
	t_vec3	shadow_dir;
	double	dist;

	shadow_dir = vector_sub(light_pos, hit_point);
	dist = vector_length(shadow_dir);
	shadow_dir = vector_norm(shadow_dir);
	if (map->bvh && map->bvh->root)
		return (is_in_shadow_bvh(map->bvh->root, hit_point, shadow_dir, dist));
	return (NO);
}

static t_color	add_specular(t_vec3 light_dir, t_vec3 normal, t_vec3 view_dir,
		t_light *light)
{
	t_vec3	reflect_v;
	double	spec_dot;
	double	specular;
	t_color	color;

	color = create_color(0, 0, 0);
	reflect_v = vector_reflect(vector_mult(light_dir, -1), normal);
	spec_dot = vector_dot_product(reflect_v, view_dir);
	if (spec_dot > 0)
	{
		specular = pow(spec_dot, 50) * light->ratio;
		color = color_mult(light->color, specular);
	}
	return (color);
}

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

t_obj	*get_closest_obj(t_ray ray, t_obj *obj, uint16_t amount_obj,
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

t_color	trace_ray(t_ray ray, t_bvh *bvh, t_map *map, int depth)
{
	t_obj	*closest_obj;
	t_vec3	hit_point;
	t_vec3	normal;
	t_color	local_color;
	t_color	reflect_color;
	t_ray	reflect_ray;
	double	min_t;

	if (depth <= 0)
		return (get_background_color(ray));
	closest_obj = NULL;
	min_t = INFINITY;
	closest_obj = get_closest_obj_from_bvh(ray, bvh->root, &min_t);
	if (!closest_obj)
		return (get_background_color(ray));
	hit_point = ray_at_pos(ray, min_t);
	normal = closest_obj->methods->get_normal(closest_obj, hit_point);
	if (vector_dot_product(normal, ray.direction) > 0)
		normal = vector_mult(normal, -1);
	local_color = calculate_light(map, closest_obj, hit_point);
	if (closest_obj->reflection > 0)
	{
		reflect_ray.direction = vector_reflect(ray.direction, normal);
		reflect_ray.start = vector_add(hit_point, vector_mult(normal, 100
					* EPSILON));
		reflect_color = trace_ray(reflect_ray, bvh, map, depth - 1);
		return (color_mix(local_color, reflect_color, closest_obj->reflection));
	}
	return (local_color);
}
