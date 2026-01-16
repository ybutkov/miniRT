/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_internal.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybutkov <ybutkov@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/16 16:47:39 by ybutkov           #+#    #+#             */
/*   Updated: 2026/01/16 16:57:08 by ybutkov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RAY_INTERNAL_H
# define RAY_INTERNAL_H

# include "bvh.h"
# include "rays.h"

t_obj	*get_closest_obj_from_bvh(t_ray ray, t_bvh_node *node, double *min_t);
t_color	calculate_light(t_map *map, t_obj *obj, t_vec3 hit_point);
t_color	add_specular(t_vec3 light_dir, t_vec3 normal, t_vec3 view_dir,
			t_light *light);
int		is_in_shadow(t_map *map, t_vec3 hit_point, t_vec3 light_pos);

#endif