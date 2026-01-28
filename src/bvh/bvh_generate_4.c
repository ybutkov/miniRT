/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bvh_generate_4.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybutkov <ybutkov@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/21 18:52:15 by ybutkov           #+#    #+#             */
/*   Updated: 2026/01/27 14:46:57 by ybutkov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "bvh_internal.h"

t_vec3	get_centroid(t_obj *obj)
{
	t_aabb	aabb;

	ft_bzero(&aabb, sizeof(t_aabb));
	aabb = obj->methods->get_aabb(obj);
	return (vector_mult(vector_add(aabb.min, aabb.max), 0.5f));
}

void	init_bounds(t_vec3 *bounds)
{
	bounds[0] = create_vector(INFINITY, INFINITY, INFINITY);
	bounds[1] = create_vector(-INFINITY, -INFINITY, -INFINITY);
}

int	get_split_axis(t_vec3 extent)
{
	int	axis;

	axis = 0;
	if (extent.v[1] > extent.v[0])
		axis = 1;
	if (extent.v[2] > extent.v[axis])
		axis = 2;
	return (axis);
}

double	get_best_split_pos(t_bvh_node *node, int *axis, t_obj **obj, int amount)
{
	t_vec3	extent;
	t_vec3	bounds[2];
	t_vec3	c;
	int		i;

	extent = vector_sub(node->aabb.max, node->aabb.min);
	*axis = get_split_axis(extent);
	init_bounds(bounds);
	i = 0;
	while (i < amount)
	{
		c = get_centroid(obj[i]);
		bounds[0] = vector_min(bounds[0], c);
		bounds[1] = vector_max(bounds[1], c);
		i++;
	}
	return ((bounds[0].v[*axis] + bounds[1].v[*axis]) * 0.5f);
}

void	sort_centroids(double *centroids, int amount)
{
	int		i;
	int		j;
	double	temp;

	i = 0;
	while (i < amount - 1)
	{
		j = i + 1;
		while (j < amount)
		{
			if (centroids[j] < centroids[i])
			{
				temp = centroids[i];
				centroids[i] = centroids[j];
				centroids[j] = temp;
			}
			j++;
		}
		i++;
	}
}
