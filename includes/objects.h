/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   objects.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybutkov <ybutkov@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/03 23:50:39 by ybutkov           #+#    #+#             */
/*   Updated: 2026/01/04 19:12:49 by ybutkov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef OBJECTS_H
# define OBJECTS_H

# include "colors.h"
# include "vectors.h"

// typedef t_vec3			t_color;
typedef struct s_obj	t_obj;
typedef struct s_map	t_map;

typedef t_vec3			(*t_get_normal)(t_obj *this, t_vec3 point);
typedef double			(*t_intersect)(t_obj *this, t_vec3 pos, t_vec3 dir);

typedef struct s_vtable
{
	t_get_normal		get_normal;
	t_intersect			intersect;
}						t_vtable;

typedef struct s_obj
{
	t_vtable			*methods;
	t_color				color;
	double				brightness;
	void				*data;
	struct s_obj		*next;
}						t_obj;

typedef struct s_sphere
{
	t_vec3				center;
	double				radius;
	double				radius_sq;
}						t_sphere;

typedef struct s_camera
{
	t_vec3				pos;
	t_vec3				dir;
	int					fov;
	double				aspect_ratio;
	t_vec3				horizontal;
	t_vec3				vertical;
	t_vec3				lower_left_pos;
}						t_camera;

t_obj					*create_sphere(t_vec3 pos, double diametr,
							t_color color);
t_camera				create_camera(t_vec3 pos, t_vec3 dir, double fov,
							t_map *map);
int						solve_quadratic(t_vec3 abc, double *t1, double *t2);

#endif