/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   object_selection.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybutkov <ybutkov@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/08 19:22:19 by ybutkov           #+#    #+#             */
/*   Updated: 2026/01/21 20:37:59 by ybutkov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "constants.h"
#include "miniRT.h"
#include "point.h"
#include "rays.h"
#include "vectors.h"
#include <math.h>

t_obj	*select_object_at_screen_pos(t_app *app, int screen_x, int screen_y)
{
	t_ray	ray;
	t_obj	*obj;
	t_obj	*closest_obj;
	double	t;
	double	min_t;
	t_ratio	ratio;

	ratio.x = (double)screen_x / (double)app->width;
	ratio.y = (double)screen_y / (double)app->height;
	ray = get_ray(app->map->camera, ratio.x, ratio.y);
	closest_obj = NULL;
	min_t = INFINITY;
	obj = app->map->objects;
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
	return (closest_obj);
}

void	move_selected_object(t_app *app, int delta_x, int delta_y)
{
	t_obj		*obj;
	t_sphere	*sphere;
	t_vec3		movement;
	t_vec3		right;
	t_vec3		up;

	if (!app->selected_obj)
		return ;
	obj = app->selected_obj;
	right = app->map->camera->right;
	up = app->map->camera->up;
	movement = vector_add(vector_mult(right, (double)delta_x * 0.05),
			vector_mult(up, (double)(-delta_y) * 0.05));
	if (obj->data)
	{
		if (obj->methods == NULL)
			return ;
		if (obj == app->map->objects || obj->methods->intersect == NULL)
			return ;
		sphere = (t_sphere *)obj->data;
		sphere->center = vector_add(sphere->center, movement);
		app->map->is_change = 1;
	}
}
