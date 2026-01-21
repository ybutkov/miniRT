/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_func_2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybutkov <ybutkov@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/03 21:36:28 by ybutkov           #+#    #+#             */
/*   Updated: 2026/01/16 16:57:37 by ybutkov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "bvh.h"
#include "constants.h"
#include "map.h"
#include "objects.h"
#include "rays.h"
#include "vectors.h"
#include <math.h>
#include <stdlib.h>
#include <unistd.h>

static int	is_in_shadow_bvh(t_bvh_node *node, t_vec3 origin, t_vec3 dir,
		double max_dist)
{
	t_obj		*obj;
	double		t;
	uint16_t	amount;

	if (!node || intersect_aabb(node->aabb, origin, dir) == -1.0)
		return (NO);
	if (node->is_leaf == OK)
	{
		obj = node->obj;
		amount = node->amount_obj;
		while (amount > 0)
		{
			t = obj->methods->intersect(obj, origin, dir);
			if (t > EPSILON && t < max_dist)
				return (OK);
			obj = obj->next;
			amount--;
		}
		return (NO);
	}
	if (node->left && is_in_shadow_bvh(node->left, origin, dir, max_dist))
		return (OK);
	if (node->right && is_in_shadow_bvh(node->right, origin, dir, max_dist))
		return (OK);
	return (NO);
}

int	is_in_shadow(t_map *map, t_vec3 hit_point, t_vec3 light_pos)
{
	t_vec3	shadow_dir;
	double	dist;

	shadow_dir = vector_sub(light_pos, hit_point);
	dist = vector_length(shadow_dir);
	shadow_dir = vector_norm(shadow_dir);
	if (map->bvh && map->bvh->root)
		return (is_in_shadow_bvh(map->bvh->root, hit_point, shadow_dir, dist));
	return (NO);
}

t_color	add_specular(t_vec3 light_dir, t_vec3 normal, t_vec3 view_dir,
		t_light *light)
{
	t_vec3	reflect_v;
	double	spec_dot;
	double	specular;
	t_color	color;

	color = create_color(0, 0, 0);
	reflect_v = vector_reflect(vector_mult(light_dir, -1), normal);
	spec_dot = vector_dot_product(reflect_v, view_dir);
	if (spec_dot > 0)
	{
		specular = pow(spec_dot, 50) * light->ratio;
		color = color_mult(light->color, specular);
	}
	return (color);
}
