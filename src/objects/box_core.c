/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   box_core.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybutkov <ybutkov@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/10 14:02:39 by ybutkov           #+#    #+#             */
/*   Updated: 2026/01/10 21:02:25 by ybutkov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "constants.h"
#include "objects.h"
#include <stdlib.h>
#include <math.h>

t_obj_type	box_get_type(void)
{
	return (BOX);
}

double	box_intersect(t_obj *this, t_vec3 origin, t_vec3 dir)
{
	t_box	*b;
	t_vec3	local_rel;
	t_vec3	local_dir;
	t_vec3	inv_dir;
	double	t[6];
	double	res[2];

	b = (t_box *)this->data;
	local_rel = vector_sub(origin, b->center);
	local_dir = create_vector(vector_dot_product(dir, b->axis[0]),
			vector_dot_product(dir, b->axis[1]), vector_dot_product(dir, b->axis[2]));
	local_rel = create_vector(vector_dot_product(local_rel, b->axis[0]),
			vector_dot_product(local_rel, b->axis[1]),
			vector_dot_product(local_rel, b->axis[2]));
	inv_dir = create_vector(1.0 / local_dir.x, 1.0 / local_dir.y, 1.0 / local_dir.z);
	t[0] = (-b->half_size.x - local_rel.x) * inv_dir.x;
	t[1] = (b->half_size.x - local_rel.x) * inv_dir.x;
	t[2] = (-b->half_size.y - local_rel.y) * inv_dir.y;
	t[3] = (b->half_size.y - local_rel.y) * inv_dir.y;
	t[4] = (-b->half_size.z - local_rel.z) * inv_dir.z;
	t[5] = (b->half_size.z - local_rel.z) * inv_dir.z;
	res[0] = fmax(fmax(fmin(t[0], t[1]), fmin(t[2], t[3])), fmin(t[4], t[5]));
	res[1] = fmin(fmin(fmax(t[0], t[1]), fmax(t[2], t[3])), fmax(t[4], t[5]));
	if (res[1] < 0 || res[0] > res[1])
		return (-1.0);
	if (res[0] > EPSILON)
		return (res[0]);
	return (res[1]);
}

t_vec3	box_get_normal(t_obj *this, t_vec3 pos)
{
	t_box	*box;
	t_vec3	d;
	double	min_dist;
	double	dist;
	double	points[3];
	int		axis;
	int		i;

	box = (t_box *)this->data;
	d = vector_sub(pos, box->center);
	min_dist = INFINITY;
	axis = 0;
	i = 0;
	while (i < 3)
	{
		points[i] = vector_dot_product(d, box->axis[i]);
		dist = fabs(box->half_size.v[i] - fabs(points[i]));
		if (dist < min_dist)
		{
			min_dist = dist;
			axis = i;
		}
		i++;
	}
	if (points[axis] > 0)
		return (box->axis[axis]);
	return (vector_mult(box->axis[axis], -1));
}

t_vtable	*get_box_methods(void)
{
	static t_vtable	box_methods;
	static int		is_init;

	if (!is_init)
	{
		box_methods.get_normal = box_get_normal;
		box_methods.intersect = box_intersect;
		box_methods.get_type = box_get_type;
		is_init = 1;
	}
	return (&box_methods);
}

t_obj	*create_box(t_vec3 center, t_vec3 orientation, t_vec3 size,
		t_color color, double reflection)
{
	t_obj	*obj;
	t_box	*box;
	t_vec3	up;

	obj = create_obj(color, reflection, DEFAULT_BRIGHTNESS);
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
