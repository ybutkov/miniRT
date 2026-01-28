/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bvh_internal.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybutkov <ybutkov@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/21 16:54:58 by ybutkov           #+#    #+#             */
/*   Updated: 2026/01/28 13:30:07 by ybutkov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BVH_INTERNAL_H
# define BVH_INTERNAL_H

# include "bvh.h"
# include "constants.h"
# include "libft.h"
# include <math.h>
# include <stdlib.h>

typedef struct s_bvh_data
{
	t_bvh	*bvh;
	t_obj	*obj;
	t_obj	**arr;
	int		plane_count;
}			t_bvh_data;

void		free_bvh(t_bvh *this);
t_aabb		create_infinite_aabb(void);
t_aabb		calculate_aabb_array(t_obj **obj, int amount);
int			handle_only_planes(t_bvh *bvh, t_obj *obj, int plane_count);
int			count_planes(t_obj *obj, t_obj *first_non_plane);
t_obj		*move_planes_to_head(t_obj **obj);

void		process_plane(t_obj *curr, t_obj *prev, t_obj **obj,
				t_obj **planes);
void		generate_bvh_node(t_bvh_node *node, t_obj **obj, int amount);
void		recurse_bvh_nodes(t_bvh_node *node, t_obj **obj, int amount,
				int left_count);
void		create_child_nodes(t_bvh_node *node, t_obj **obj, int amount,
				int left_count);
void		partition_objects(t_obj **obj, double split_pos, int axis,
				int *count);

void		link_objects_in_array(t_obj **obj, int amount);
int			get_obj_count(t_obj *obj);
t_aabb		calculate_aabb_array(t_obj **obj, int amount);
double		get_median_split_pos(t_bvh_node *node, int *axis, t_obj **obj,
				int amount);
void		fill_centroids(t_obj **obj, double *centroids, int axis,
				int amount);

void		sort_centroids(double *centroids, int amount);
double		get_best_split_pos(t_bvh_node *node, int *axis, t_obj **obj,
				int amount);
int			get_split_axis(t_vec3 extent);
void		init_bounds(t_vec3 *bounds);
t_vec3		get_centroid(t_obj *obj);

#endif
