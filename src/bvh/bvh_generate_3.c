/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bvh_generate_3.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybutkov <ybutkov@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/21 18:50:38 by ybutkov           #+#    #+#             */
/*   Updated: 2026/01/21 18:55:14 by ybutkov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "bvh_internal.h"

void	fill_centroids(t_obj **obj, double *centroids, int axis, int amount)
{
	int	i;

	i = 0;
	while (i < amount)
	{
		centroids[i] = get_centroid(obj[i]).v[axis];
		i++;
	}
}

double	get_median_split_pos(t_bvh_node *node, int *axis, t_obj **obj,
		int amount)
{
	double	*centroids;
	t_vec3	extent;
	double	pos;

	extent = vector_sub(node->aabb.max, node->aabb.min);
	*axis = get_split_axis(extent);
	centroids = malloc(amount * sizeof(double));
	if (!centroids)
	{
		pos = node->aabb.min.v[*axis] + node->aabb.max.v[*axis];
		return (pos * 0.5);
	}
	fill_centroids(obj, centroids, *axis, amount);
	sort_centroids(centroids, amount);
	pos = centroids[amount / 2];
	free(centroids);
	return (pos);
}

t_aabb	calculate_aabb_array(t_obj **obj, int amount)
{
	t_aabb	cur_aabb;
	t_aabb	aabb;
	int		i;

	ft_bzero(&aabb, sizeof(t_aabb));
	ft_bzero(&cur_aabb, sizeof(t_aabb));
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

void	link_objects_in_array(t_obj **obj, int amount)
{
	int	i;

	i = 0;
	while (i < amount - 1)
	{
		obj[i]->next = obj[i + 1];
		i++;
	}
	if (amount > 0)
		obj[amount - 1]->next = NULL;
}
