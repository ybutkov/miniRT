/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_core.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybutkov <ybutkov@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/03 21:36:28 by ybutkov           #+#    #+#             */
/*   Updated: 2026/01/07 17:15:58 by ybutkov          ###   ########.fr       */
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
	t_vec3	sh_hit_point;
	t_vec3	reflect_v;
	double	total_intensity;
	double	dot;
	double	spec_dot;

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
		sh_hit_point = vector_add(hit_point, vector_mult(normal, 0.01));
		if (dot > 0 && is_in_shadow(map, sh_hit_point, curr->pos) == NO)
		{
			total_intensity += dot * curr->ratio;
			reflect_v = vector_reflect(vector_mult(light_direct, -1), normal);
			spec_dot = vector_dot_product(reflect_v, view_dir);
			if (spec_dot > 0)
				total_intensity += pow(spec_dot, 50) * curr->ratio;
		}
		curr = curr->next;
	}
	if (total_intensity > 1.0)
		total_intensity = 1.0;
	return (color_mult(obj->color, total_intensity));
}

t_color	trace_ray(t_ray ray, t_obj *obj, t_map *map, int depth)
{
	t_obj	*closest_obj;
	t_vec3	hit_point;
	t_vec3	normal;
	t_color	local_color;
	t_ray	reflect_ray;
	double	min_t;
	double	t;

	if (depth <= 0)
		return (get_background_color(ray));
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
	normal = closest_obj->methods->get_normal(closest_obj, hit_point);
	if (vector_dot_product(normal, ray.direction) > 0)
		normal = vector_mult(normal, -1);
	local_color = calculate_light(map, closest_obj, hit_point);
	if (closest_obj->reflection > 0)
	{
		reflect_ray.direction = vector_reflect(ray.direction, normal);
		reflect_ray.start = vector_add(hit_point, vector_mult(normal, 100 * EPSILON));
		t_color reflect_color = trace_ray(reflect_ray, map->objects, map, depth - 1);
		return (color_mix(local_color, reflect_color, closest_obj->reflection));
	}
	return (local_color);
}
