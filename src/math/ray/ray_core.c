/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_core.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybutkov <ybutkov@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/03 21:36:28 by ybutkov           #+#    #+#             */
/*   Updated: 2026/01/05 22:43:07 by ybutkov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "map.h"
#include "objects.h"
#include "rays.h"
#include "vectors.h"
#include "constants.h"
#include <math.h>
#include <stdlib.h>

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

t_ray	get_ray(t_camera cam, double x_ratio, double y_ratio)
{
	t_vec3 target;
	t_vec3 direction;

	target = vector_add(cam.lower_left_pos,
			vector_add(vector_mult(cam.horizontal, x_ratio),
				vector_mult(cam.vertical, y_ratio)));
	direction = vector_sub(target, cam.pos);
	return (create_ray(cam.pos, direction));
}

int	is_in_shadow(t_map *map, t_vec3 hit_point, t_vec3 light_pos)
{
	t_obj	*curr;
	t_vec3	shadow_dir;
	t_vec3	shadow_original;
	double	dist;
	double	t;

	shadow_dir = vector_sub(light_pos, hit_point);
	dist = vector_length(shadow_dir);
	shadow_dir = vector_norm(shadow_dir);
	shadow_original = vector_add(hit_point, vector_mult(shadow_dir, EPSILON));
	curr = map->objects;
	while (curr)
	{
		t = curr->methods->intersect(curr, shadow_original, shadow_dir);
		if (t > EPSILON && t < dist)
			return (OK);
		curr = curr->next;
	}
	return (NO);
}


t_color	calculate_light(t_map *map, t_obj *obj, t_vec3 hit_point)
{
	t_light	*curr;
	t_vec3	normal;
	t_vec3	view_dir;
	t_vec3	light_direct;
	double	total_intensity;
	double	dot;

	normal = obj->methods->get_normal(obj, hit_point);
	view_dir = vector_norm(vector_sub(map->camera.pos, hit_point));
	if (vector_dot_product(normal, view_dir) < 0)
		normal = vector_mult(normal, -1);
	total_intensity = map->ambient.ratio;
	curr = map->lights;
	while (curr)
	{
		light_direct = vector_norm(vector_sub(curr->pos, hit_point));
		dot = vector_dot_product(normal, light_direct);
		if (dot > 0 && is_in_shadow(map, hit_point, curr->pos) == NO)
			total_intensity += dot * curr->ratio;
		curr = curr->next;
	}
	if (total_intensity > 1.0)
		total_intensity = 1.0;
	return (color_mult(obj->color, total_intensity));
}

t_color	trace_ray(t_ray ray, t_obj *obj, t_map *map)
{
	t_obj	*closest_obj;
	t_vec3	hit_point;
	double	min_t;
	double	t;

	closest_obj = NULL;
	min_t = INFINITY;
	while (obj)
	{
		t = obj->methods->intersect(obj, ray.start, ray.direction);
		if (t > EPSILON && t < min_t)
		{
			min_t = t;
			closest_obj = obj;
		}
		obj = obj->next;
	}
	if (!closest_obj)
		return (get_background_color(ray));
	hit_point = ray_at_pos(ray, min_t);
	return (calculate_light(map, closest_obj, hit_point));
}
