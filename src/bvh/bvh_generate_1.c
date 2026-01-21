/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bvh_generate_1.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybutkov <ybutkov@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/21 18:10:11 by ybutkov           #+#    #+#             */
/*   Updated: 2026/01/21 18:56:20 by ybutkov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "bvh_internal.h"

t_obj	*move_planes_to_head(t_obj **obj)
{
	t_obj	*current;
	t_obj	*prev;
	t_obj	*planes_arr[2];

	current = *obj;
	prev = NULL;
	planes_arr[0] = NULL;
	planes_arr[1] = NULL;
	while (current)
	{
		if (current->methods->get_type() == PLANE)
			process_plane(current, prev, obj, planes_arr);
		else
			prev = current;
		current = current->next;
	}
	if (planes_arr[0])
	{
		planes_arr[1]->next = *obj;
		*obj = planes_arr[0];
		return (planes_arr[1]->next);
	}
	return (*obj);
}

int	count_planes(t_obj *obj, t_obj *first_non_plane)
{
	int	count;

	count = 0;
	while (obj != first_non_plane)
	{
		count++;
		obj = obj->next;
	}
	return (count);
}

t_aabb	calculate_aabb(t_obj *obj, int amount)
{
	t_aabb	cur_aabb;
	t_aabb	aabb;
	t_obj	*cur;

	aabb.min = create_vector(INFINITY, INFINITY, INFINITY);
	aabb.max = create_vector(-INFINITY, -INFINITY, -INFINITY);
	cur = obj;
	while (cur && amount--)
	{
		cur_aabb = cur->methods->get_aabb(cur);
		aabb.min = vector_min(aabb.min, cur_aabb.min);
		aabb.max = vector_max(aabb.max, cur_aabb.max);
		cur = cur->next;
	}
	return (aabb);
}

t_aabb	create_infinite_aabb(void)
{
	t_aabb	aabb;

	aabb.min = create_vector(-INFINITY, -INFINITY, -INFINITY);
	aabb.max = create_vector(INFINITY, INFINITY, INFINITY);
	return (aabb);
}

int	handle_only_planes(t_bvh *bvh, t_obj *obj, int plane_count)
{
	if (plane_count > 0)
	{
		bvh->root = create_bvh_node(create_infinite_aabb(), obj, plane_count);
		if (bvh->root)
			bvh->root->is_leaf = OK;
	}
	return (OK);
}
