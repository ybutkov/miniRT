/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bvh_node_core.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybutkov <ybutkov@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/11 19:12:11 by ybutkov           #+#    #+#             */
/*   Updated: 2026/01/17 17:12:42 by ybutkov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "bvh.h"
#include "constants.h"
#include <math.h>
#include <stdlib.h>

double	intersect_aabb(t_aabb aabb, t_vec3 origin, t_vec3 dir)
{
	t_vec3	inv_dir;
	double	t[6];
	double	res[2];

	inv_dir = create_vector(1.0 / dir.x, 1.0 / dir.y, 1.0 / dir.z);
	t[0] = (aabb.min.x - origin.x) * inv_dir.x;
	t[1] = (aabb.max.x - origin.x) * inv_dir.x;
	t[2] = (aabb.min.y - origin.y) * inv_dir.y;
	t[3] = (aabb.max.y - origin.y) * inv_dir.y;
	t[4] = (aabb.min.z - origin.z) * inv_dir.z;
	t[5] = (aabb.max.z - origin.z) * inv_dir.z;
	res[0] = fmax(fmax(fmin(t[0], t[1]), fmin(t[2], t[3])), fmin(t[4], t[5]));
	res[1] = fmin(fmin(fmax(t[0], t[1]), fmax(t[2], t[3])), fmax(t[4], t[5]));
	if (res[1] < EPSILON || res[0] > res[1])
		return (-1.0);
	if (res[0] > EPSILON)
		return (res[0]);
	return (res[1]);
}

t_bvh_node	*create_bvh_node(t_aabb aabb, t_obj *obj, uint16_t amount_obj)
{
	t_bvh_node	*bvh_node;

	bvh_node = malloc(sizeof(t_bvh_node));
	if (bvh_node == NULL)
		return (HANDLE_ERROR_NULL);
	bvh_node->aabb = aabb;
	bvh_node->obj = obj;
	bvh_node->amount_obj = amount_obj;
	bvh_node->is_leaf = NO;
	bvh_node->left = NULL;
	bvh_node->right = NULL;
	return (bvh_node);
}
