/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_core.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybutkov <ybutkov@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/03 21:36:28 by ybutkov           #+#    #+#             */
/*   Updated: 2026/01/04 22:06:41 by ybutkov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "objects.h"
#include "rays.h"
#include "vectors.h"
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

t_color	trace_ray(t_ray ray, t_obj *obj)
{
	t_obj	*closest_obj;
	double	min_t;
	double	t;

	closest_obj = NULL;
	min_t = INFINITY;
	while (obj)
	{
		t = obj->methods->intersect(obj, ray.start, ray.direction);
		if (t > 0 && t < min_t)
		{
			min_t = t;
			closest_obj = obj;
		}
		obj = obj->next;
	}
	if (closest_obj)
		return (closest_obj->color);
	// return (get_background_color(ray));
	return (create_color(0,0,0));
}
