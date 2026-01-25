/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_core.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybutkov <ybutkov@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/03 21:36:28 by ybutkov           #+#    #+#             */
/*   Updated: 2026/01/16 17:00:01 by ybutkov          ###   ########.fr       */
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

static t_color	get_reflect_color(t_ray ray, t_map *map, int depth,
	t_hit_info	hit_info)
{
	t_ray	reflect_ray;
	t_color	reflect_color;

	reflect_ray.direction = vector_reflect(ray.direction, hit_info.normal);
	reflect_ray.start = vector_add(hit_info.hit_point,
			vector_mult(hit_info.normal, 100 * EPSILON));
	reflect_color = trace_ray(reflect_ray, map, depth - 1);
	return (reflect_color);
}

t_color	trace_ray(t_ray ray, t_map *map, int depth)
{
	t_obj		*closest_obj;
	t_hit_info	hit_info;
	t_color		local_color;
	double		min_t;

	if (depth <= 0)
		return (get_background_color(ray, map));
	closest_obj = NULL;
	min_t = INFINITY;
	closest_obj = get_closest_obj_from_bvh(ray, map->bvh->root, &min_t);
	if (!closest_obj)
		return (get_background_color(ray, map));
	hit_info.hit_point = ray_at_pos(ray, min_t);
	hit_info.normal = closest_obj->methods->get_normal(closest_obj,
			hit_info.hit_point);
	if (vector_dot_product(hit_info.normal, ray.direction) > 0)
		hit_info.normal = vector_mult(hit_info.normal, -1);
	local_color = calculate_light(map, closest_obj, hit_info.hit_point);
	if (closest_obj->reflection > 0)
	{
		return (color_mix(local_color, get_reflect_color(ray, map, depth,
					hit_info), closest_obj->reflection));
	}
	return (local_color);
}
