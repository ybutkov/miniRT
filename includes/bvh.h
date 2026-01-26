/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bvh.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybutkov <ybutkov@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/10 23:57:03 by ybutkov           #+#    #+#             */
/*   Updated: 2026/01/11 22:31:23 by ybutkov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BVH_H
# define BVH_H

# include "objects.h"
# include "rays.h"
# include "vectors.h"
# include <stdint.h>

typedef struct s_bvh_node
{
	t_aabb				aabb;
	t_obj				*obj;
	uint16_t			amount_obj;
	struct s_bvh_node	*left;
	struct s_bvh_node	*right;
	int					is_leaf;
}						t_bvh_node;

typedef struct s_bvh
{
	t_bvh_node			*root;
	void				*mlx;
	int					(*build)(struct s_bvh *this, t_obj *obj);
	void				(*free)(struct s_bvh *this);
}						t_bvh;

t_bvh					*create_bvh(void);
t_bvh_node				*create_bvh_node(t_aabb aabb, t_obj *obj,
							uint16_t amount_obj);
double					intersect_aabb(t_aabb aabb, t_vec3 origin, t_vec3 dir);

#endif