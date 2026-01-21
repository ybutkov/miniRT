/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   obj_internal.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybutkov <ybutkov@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/15 13:41:52 by ybutkov           #+#    #+#             */
/*   Updated: 2026/01/15 21:52:20 by ybutkov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef OBJ_INTERNAL_H

# define OBJ_INTERNAL_H

# include "objects.h"
# include "vectors.h"

typedef struct s_box_normal_utils
{
	t_vec3	d;
	double	min_dist;
	double	dist;
	double	points[3];
	int		axis;
}			t_box_normal_utils;

// BOX
t_vec3		box_get_normal(t_obj *this, t_vec3 pos);
t_vtable	*get_box_methods(void);
t_obj_type	box_get_type(void);
t_aabb		box_get_aabb(t_obj *this);
double		box_intersect(t_obj *this, t_vec3 origin, t_vec3 dir);

// CYLINDER
t_vec3		cylinder_get_normal(t_obj *this, t_vec3 pos);
t_vtable	*get_cylinder_methods(void);
t_obj_type	cylinder_get_type(void);
t_aabb		cylinder_get_aabb(t_obj *this);
double		cylinder_intersect(t_obj *this, t_vec3 origin, t_vec3 dir);

// PLANE
t_vec3		plane_get_normal(t_obj *this, t_vec3 pos);
t_vtable	*get_plane_methods(void);
t_obj_type	plane_get_type(void);
t_aabb		plane_get_aabb(t_obj *this);
double		plane_intersect(t_obj *this, t_vec3 origin, t_vec3 dir);

// SPHERE
t_vec3		sphere_get_normal(t_obj *this, t_vec3 pos);
t_vtable	*get_sphere_methods(void);
t_obj_type	sphere_get_type(void);
t_aabb		sphere_get_aabb(t_obj *this);
double		sphere_intersect(t_obj *this, t_vec3 origin, t_vec3 dir);

// TRIANGLE
t_vec3		triangle_get_normal(t_obj *this, t_vec3 pos);
t_vtable	*get_triangle_methods(void);
t_obj_type	triangle_get_type(void);
t_aabb		triangle_get_aabb(t_obj *this);
double		triangle_intersect(t_obj *this, t_vec3 origin, t_vec3 dir);

#endif