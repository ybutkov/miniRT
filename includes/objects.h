/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   objects.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybutkov <ybutkov@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/03 23:50:39 by ybutkov           #+#    #+#             */
/*   Updated: 2026/01/11 00:17:34 by ybutkov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef OBJECTS_H
# define OBJECTS_H

# include "colors.h"
# include "vectors.h"

typedef enum e_obj_type
{
	SPHERE,
	PLANE,
	CYLINDER,
	TRIANGLE,
	BOX
}						t_obj_type;

typedef struct			s_aabb
{
	t_vec3				min;
	t_vec3				max;
}						t_aabb;

// typedef t_vec3			t_color;
typedef struct s_obj	t_obj;
typedef struct s_map	t_map;

typedef t_vec3			(*t_get_normal)(t_obj *this, t_vec3 point);
typedef double			(*t_intersect)(t_obj *this, t_vec3 pos, t_vec3 dir);
typedef t_aabb			(*t_get_aabb)(t_obj *this);
typedef t_obj_type		(*t_get_type)(void);

typedef struct s_vtable
{
	t_get_normal		get_normal;
	t_intersect			intersect;
	t_get_aabb			get_aabb;
	t_get_type			get_type;
}						t_vtable;

typedef struct s_obj
{
	t_vtable			*methods;
	t_color				color;
	double				brightness;
	double				reflection;
	void				*data;
	struct s_obj		*next;
}						t_obj;

typedef struct s_sphere
{
	t_vec3				center;
	double				radius;
	double				radius_sq;
}						t_sphere;
typedef struct s_cylinder
{
	t_vec3				center;
	t_vec3				normal;
	double				radius;
	double				radius_sq;
	double				height;
}						t_cylinder;

typedef struct s_triangle
{
	t_vec3				p_1;
	t_vec3				p_2;
	t_vec3				p_3;
	t_vec3				normal;
}						t_triangle;

typedef struct s_box
{
	t_vec3				center;
	t_vec3				axis[3];
	t_vec3				half_size;
}						t_box;

typedef struct s_light
{
	t_vec3				pos;
	double				ratio;
	t_color				color;
	struct s_light		*next;
}						t_light;

typedef struct s_ambient
{
	double				ratio;
	t_color				color;
}						t_ambient;

typedef struct s_plane
{
	t_vec3				point;
	t_vec3				normal;
	t_color				color;
}						t_plane;

// dir, right, up (w,u,v)
typedef struct s_camera
{
	t_vec3				pos;
	t_vec3				dir;
	t_vec3				right;
	t_vec3				up;
	int					fov;
	double				aspect_ratio;
	t_vec3				horizontal;
	t_vec3				vertical;
	t_vec3				lower_left_pos;
}						t_camera;

t_obj					*create_obj(t_color color, double reflection,
							double brightness);
t_obj					*create_plane(t_vec3 point, t_vec3 normal,
							t_color color, double reflection);
t_obj					*create_sphere(t_vec3 pos, double diametr,
							t_color color, double reflection);
t_obj					*create_cylinder(t_vec3 pos, t_vec3 normal,
							double diametr, double height, t_color color,
							double reflection);
t_obj					*create_triangle(t_vec3 p_1, t_vec3 p_2, t_vec3 p_3,
							t_color color, double reflection);
t_obj					*create_box(t_vec3 center, t_vec3 orientation,
							t_vec3 size, t_color color, double reflection);

t_camera				*create_camera(t_vec3 pos, t_vec3 dir, double fov,
							t_map *map);
void					update_camera(t_camera *cam);
void					rotate_camera(t_camera *cam, t_vec3 dir, double delta);
int						solve_quadratic(t_vec3 abc, double *t1, double *t2);
t_light					*create_light(t_vec3 pos, double ratio, t_color color);
t_ambient				*create_ambient(double ratio, t_color color);
//
double					plane_intersect(t_obj *this, t_vec3 origin, t_vec3 dir);

#endif