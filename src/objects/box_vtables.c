/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   box_vtables.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybutkov <ybutkov@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/25 23:15:54 by ybutkov           #+#    #+#             */
/*   Updated: 2026/01/25 23:20:19 by ybutkov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "constants.h"
#include "obj_internal.h"
#include "objects.h"
#include "parser.h"
#include <math.h>
#include <stdlib.h>

t_obj_type	box_get_type(void)
{
	return (BOX);
}

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

t_vtable	*get_box_methods(void)
{
	static t_vtable	box_methods;
	static int		is_init;

	if (!is_init)
	{
		box_methods.get_normal = box_get_normal;
		box_methods.intersect = box_intersect;
		box_methods.get_aabb = box_get_aabb;
		box_methods.get_type = box_get_type;
		box_methods.get_color = default_get_color;
		is_init = 1;
	}
	return (&box_methods);
}
