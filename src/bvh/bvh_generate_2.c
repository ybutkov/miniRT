/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bvh_generate_2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybutkov <ybutkov@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/21 18:43:34 by ybutkov           #+#    #+#             */
/*   Updated: 2026/01/21 19:03:06 by ybutkov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "bvh_internal.h"
#include "utils.h"

void	partition_objects(t_obj **obj, double split_pos, int axis,
		int *count)
{
	int	i;
	int	j;

	i = 0;
	j = *count - 1;
	while (i <= j)
	{
		if (get_centroid(obj[i]).v[axis] < split_pos)
			i++;
		else
			swap((void **)&obj[i], (void **)&obj[j--]);
	}
	*count = i;
}

void	create_child_nodes(t_bvh_node *node, t_obj **obj, int amount,
		int left_count)
{
	int		right_count;
	t_aabb	left_aabb;
	t_aabb	right_aabb;

	link_objects_in_array(obj, left_count);
	link_objects_in_array(obj + left_count, amount - left_count);
	left_aabb = calculate_aabb_array(obj, left_count);
	right_count = amount - left_count;
	right_aabb = calculate_aabb_array(obj + left_count, right_count);
	node->left = create_bvh_node(left_aabb, obj[0], left_count);
	node->right = create_bvh_node(right_aabb, obj[left_count], right_count);
}

void	recurse_bvh_nodes(t_bvh_node *node, t_obj **obj, int amount,
		int left_count)
{
	int	right_count;

	if (left_count > 0)
		generate_bvh_node(node->left, obj, left_count);
	right_count = amount - left_count;
	if (right_count > 0)
		generate_bvh_node(node->right, obj + left_count, right_count);
}

void	generate_bvh_node(t_bvh_node *node, t_obj **obj, int amount)
{
	double	split_pos;
	int		axis;
	int		left_count;

	split_pos = get_median_split_pos(node, &axis, obj, amount);
	left_count = amount;
	partition_objects(obj, split_pos, axis, &left_count);
	if (left_count == 0 || left_count == amount)
	{
		node->is_leaf = OK;
		return ;
	}
	create_child_nodes(node, obj, amount, left_count);
	recurse_bvh_nodes(node, obj, amount, left_count);
}

void	process_plane(t_obj *curr, t_obj *prev, t_obj **obj, t_obj **planes)
{
	t_obj	*planes_head;
	t_obj	*planes_tail;

	planes_head = planes[0];
	planes_tail = planes[1];
	if (prev)
		prev->next = curr->next;
	else
		*obj = curr->next;
	curr->next = NULL;
	if (!planes_head)
		planes_head = curr;
	else
		planes_tail->next = curr;
	planes[0] = planes_head;
	planes[1] = curr;
}
