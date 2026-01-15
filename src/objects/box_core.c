/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   box_core.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybutkov <ybutkov@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/10 14:02:39 by ybutkov           #+#    #+#             */
/*   Updated: 2026/01/15 16:00:52 by ybutkov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "constants.h"
#include "obj_internal.h"
#include "objects.h"
#include <math.h>
#include <stdlib.h>

static t_vec3	get_inv_dir(t_box *b, t_vec3 dir)
{
	t_vec3	inv_dir;
	t_vec3	local_dir;

	local_dir = create_vector(vector_dot_product(dir, b->axis[0]),
			vector_dot_product(dir, b->axis[1]), vector_dot_product(dir,
				b->axis[2]));
	inv_dir = create_vector(1.0 / local_dir.x, 1.0 / local_dir.y, 1.0
			/ local_dir.z);
	return (inv_dir);
}

double	box_intersect(t_obj *this, t_vec3 origin, t_vec3 dir)
{
	t_box	*b;
	t_vec3	local_rel;
	t_vec3	inv_dir;
	double	t[6];
	double	res[2];

	b = (t_box *)this->data;
	local_rel = vector_sub(origin, b->center);
	local_rel = create_vector(vector_dot_product(local_rel, b->axis[0]),
			vector_dot_product(local_rel, b->axis[1]),
			vector_dot_product(local_rel, b->axis[2]));
	inv_dir = get_inv_dir(b, dir);
	t[0] = (-b->half_size.x - local_rel.x) * inv_dir.x;
	t[1] = (b->half_size.x - local_rel.x) * inv_dir.x;
	t[2] = (-b->half_size.y - local_rel.y) * inv_dir.y;
	t[3] = (b->half_size.y - local_rel.y) * inv_dir.y;
	t[4] = (-b->half_size.z - local_rel.z) * inv_dir.z;
	t[5] = (b->half_size.z - local_rel.z) * inv_dir.z;
	res[0] = fmax(fmax(fmin(t[0], t[1]), fmin(t[2], t[3])), fmin(t[4], t[5]));
	res[1] = fmin(fmin(fmax(t[0], t[1]), fmax(t[2], t[3])), fmax(t[4], t[5]));
	if (res[1] < EPSILON || res[0] > res[1])
		return (-1.0);
	if (res[0] > EPSILON)
		return (res[0]);
	return (res[1]);
}

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
			vector_add(vector_sub(b_0mx[1][0], b_0mx[0][1]), b_0mx[0][2]));
	corners[2] = vector_add(b->center,
			vector_add(vector_add(b_0mx[0][0], b_0mx[1][1]), b_0mx[0][2]));
	corners[3] = vector_add(b->center,
			vector_add(vector_sub(b_0mx[1][0], b_0mx[1][1]), b_0mx[0][2]));
	corners[4] = vector_add(b->center,
			vector_add(vector_add(b_0mx[0][0], b_0mx[0][1]), b_0mx[1][2]));
	corners[5] = vector_add(b->center,
			vector_add(vector_sub(b_0mx[1][0], b_0mx[0][1]), b_0mx[1][2]));
	corners[6] = vector_add(b->center,
			vector_add(vector_add(b_0mx[0][0], b_0mx[1][1]), b_0mx[1][2]));
	corners[7] = vector_add(b->center,
			vector_sub(vector_sub(b_0mx[1][0], b_0mx[1][1]), b_0mx[1][2]));
}

t_aabb	box_get_aabb(t_obj *this)
{
	t_aabb	aabb;
	t_box	*box;
	t_vec3	corners[8];
	int		i;

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

t_obj	*create_box(t_vec3 center, t_vec3 orientation, t_vec3 size,
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
