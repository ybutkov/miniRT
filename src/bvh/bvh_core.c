/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bvh_core.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybutkov <ybutkov@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/11 00:00:49 by ybutkov           #+#    #+#             */
/*   Updated: 2026/01/12 22:16:40 by ybutkov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "bvh.h"
#include "constants.h"
#include <math.h>
#include <stdlib.h>

void	free_bvh(t_bvh *this)
{
	free(this);
}

int	calculate_amount_obj(t_obj *obj)
{
	int	amount;

	amount = 0;
	while (obj)
	{
		amount++;
		obj = obj->next;
	}
	return (amount);
}

t_vec3	get_centroid(t_obj *obj)
{
	t_aabb	aabb;

	aabb = obj->methods->get_aabb(obj);
	return (vector_mult(vector_add(aabb.min, aabb.max), 0.5f));
}

double	get_best_split_pos(t_bvh_node *node, int *axis, t_obj **obj, int amount)
{
	double	splitPos;
	t_vec3	extent;
	t_vec3	centroid_bounds_min;
	t_vec3	centroid_bounds_max;
	int		i;
	t_vec3	c;

	extent = vector_sub(node->aabb.max, node->aabb.min);
	*axis = 0;
	if (extent.y > extent.x)
		*axis = 1;
	if (extent.z > extent.v[*axis])
		*axis = 2;
	centroid_bounds_min = create_vector(INFINITY, INFINITY, INFINITY);
	centroid_bounds_max = create_vector(-INFINITY, -INFINITY, -INFINITY);
	i = 0;
	while (i < amount)
	{
		c = get_centroid(obj[i]);
		centroid_bounds_min = vector_min(centroid_bounds_min, c);
		centroid_bounds_max = vector_max(centroid_bounds_max, c);
		i++;
	}
	splitPos = (centroid_bounds_min.v[*axis] + centroid_bounds_max.v[*axis]) * 0.5f;
	return(splitPos);
}

void	swap(void **a, void **b)
{
	void	*tmp;

	tmp = *a;
	*a = *b;
	*b = tmp;
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

t_aabb	calculate_aabb_array(t_obj **obj, int amount)
{
	t_aabb	cur_aabb;
	t_aabb	aabb;
	int		i;

	aabb.min = create_vector(INFINITY, INFINITY, INFINITY);
	aabb.max = create_vector(-INFINITY, -INFINITY, -INFINITY);
	i = 0;
	while (i < amount)
	{
		cur_aabb = obj[i]->methods->get_aabb(obj[i]);
		aabb.min = vector_min(aabb.min, cur_aabb.min);
		aabb.max = vector_max(aabb.max, cur_aabb.max);
		i++;
	}
	return (aabb);
}

t_obj	**convert_list_to_array(t_obj *obj, int amount)
{
	t_obj	**obj_array;
	int		i;

	obj_array = malloc(amount * sizeof(t_obj *));
	if (obj_array == NULL)
		return (NULL);
	i = 0;
	while (obj && i < amount)
	{
		obj_array[i] = obj;
		obj = obj->next;
		i++;
	}
	return (obj_array);
}

int	get_obj_count(t_obj *obj)
{
	int	amount;

	amount = 0;
	while (obj)
	{
		amount++;
		obj = obj->next;
	}
	return (amount);
}

void	generate_bvh_node(t_bvh_node *node, t_obj **obj, int amount)
{
	double	split_pos;
	int		axis;
	int		i;
	int		j;
	int		left_count;
	int		right_count;

	split_pos = get_best_split_pos(node, &axis, obj, amount);
	i = 0;
	j = amount - 1;
	while (i <= j)
	{
		if (get_centroid(obj[i]).v[axis] < split_pos)
			i++;
		else
			swap((void **)&obj[i], (void **)&obj[j--]);
	}
	left_count = i;
	if (left_count == 0 || left_count == amount)
	{
		node->is_leaf = OK;
		return ;
	}
	node->left = create_bvh_node(calculate_aabb_array(obj, left_count), obj[0], left_count);
	right_count = amount - left_count;
	node->right = create_bvh_node(calculate_aabb_array(obj + left_count, right_count), obj[left_count], right_count);
	if (left_count > 0)
		generate_bvh_node(node->left, obj, left_count);
	if (right_count > 0)
		generate_bvh_node(node->right, obj + left_count, right_count);
}

t_obj	*find_and_move_planes(t_obj **obj)
{
	t_obj	*current;
	t_obj	*prev;
	t_obj	*next;
	t_obj	*planes_head;
	t_obj	*planes_tail;

	current = *obj;
	prev = NULL;
	planes_head = NULL;
	planes_tail = NULL;
	while (current)
	{
		next = current->next;
		if (current->methods->get_type() == PLANE)
		{
			if (prev)
				prev->next = next;
			else
				*obj = next;
			current->next = NULL;
			if (!planes_head)
				planes_head = current;
			else
				planes_tail->next = current;
			planes_tail = current;
			current = next;
		}
		else
		{
			prev = current;
			current = next;
		}
	}
	if (planes_tail)
	{
		planes_tail->next = *obj;
		*obj = planes_head;
		return (planes_tail->next);
	}
	return (*obj);
}

int	generate_bvh(t_bvh *bvh, t_obj *obj)
{
	t_obj	**obj_array;
	t_obj	*first_non_plane;
	t_obj	*planes_head;
	int		plane_count;
	int		amount;
	t_aabb	infinite_aabb;

	first_non_plane = find_and_move_planes(&obj);
	planes_head = obj;
	plane_count = 0;
	while (planes_head != first_non_plane)
	{
		plane_count++;
		planes_head = planes_head->next;
	}
	planes_head = obj;
	if (!first_non_plane)
	{
		if (plane_count > 0)
		{
			infinite_aabb.min = create_vector(-INFINITY, -INFINITY, -INFINITY);
			infinite_aabb.max = create_vector(INFINITY, INFINITY, INFINITY);
			bvh->root = create_bvh_node(infinite_aabb, obj, plane_count);
			if (bvh->root)
				bvh->root->is_leaf = OK;
		}
		return (OK);
	}
	amount = get_obj_count(first_non_plane);
	if (amount == 0)
		return (OK);
	obj_array = convert_list_to_array(first_non_plane, amount);
	if (obj_array == NULL)
		return (NO);
	infinite_aabb.min = create_vector(-INFINITY, -INFINITY, -INFINITY);
	infinite_aabb.max = create_vector(INFINITY, INFINITY, INFINITY);
	bvh->root = create_bvh_node(infinite_aabb, obj, plane_count + amount);
	if (bvh->root == NULL)
	{
		free(obj_array);
		return (NO);
	}
	if (plane_count > 0)
		bvh->root->left = create_bvh_node(infinite_aabb, planes_head, plane_count);
	bvh->root->right = create_bvh_node(calculate_aabb_array(obj_array, amount), obj_array[0], amount);
	if (plane_count > 0 && bvh->root->left)
		bvh->root->left->is_leaf = OK;
	if (bvh->root->right)
		generate_bvh_node(bvh->root->right, obj_array, amount);
	free(obj_array);
	return (OK);
}

t_bvh	*create_bvh(void)
{
	t_bvh	*bvh;

	bvh = malloc(sizeof(t_bvh));
	if (bvh == NULL)
		return (HANDLE_ERROR_NULL);
	bvh->build = generate_bvh;
	bvh->free = free_bvh;
	return (bvh);
}
