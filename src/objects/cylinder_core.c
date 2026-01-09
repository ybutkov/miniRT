/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder_core.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybutkov <ybutkov@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/06 14:43:38 by ybutkov           #+#    #+#             */
/*   Updated: 2026/01/09 14:28:15 by ybutkov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "constants.h"
#include "objects.h"
#include <stdlib.h>

t_obj_type	cylinder_get_type(void)
{
	return (CYLINDER);
}

t_vec3	cylinder_get_normal(t_obj *this, t_vec3 pos)
{
	t_cylinder	*cylinder;
	t_vec3		v;
	t_vec3		pr;
	double		h;

	cylinder = (t_cylinder *)this->data;
	v = vector_sub(pos, cylinder->center);
	h = vector_dot_product(v, cylinder->normal);
	if (h > (cylinder->height / 2.0 - EPSILON))
		return (cylinder->normal);
	if (h < (-cylinder->height / 2.0 + EPSILON))
		return (vector_mult(cylinder->normal, -1));
	pr = vector_mult(cylinder->normal, h);
	return (vector_norm(vector_sub(v, pr)));
}

double	intersect_caps(t_cylinder *cy, t_vec3 origin, t_vec3 dir,
	t_vec3 cap_center)
{
	double	t;

	(void)t;
	(void)cy;
	(void)origin;
	(void)dir;
	(void)cap_center;
	return (0);
}

double	pipe_intersect(t_cylinder *cy, t_vec3 origin, t_vec3 dir)
{
	t_vec3		oc;
	double		d_dot;
	double		oc_dot;
	t_vec3		abc;
	double		t_res;
	double		t[2];

	oc = vector_sub(origin, cy->center);
	d_dot = vector_dot_product(dir, cy->normal);
	oc_dot = vector_dot_product(oc, cy->normal);
	abc.x = vector_dot_product(dir, dir) - d_dot * d_dot;
	abc.y = 2.0 * (vector_dot_product(dir, oc) - d_dot * oc_dot);
	abc.z = vector_dot_product(oc, oc) - oc_dot * oc_dot - cy->radius_sq;
	if (solve_quadratic(abc, &t[0], &t[1]) == NO)
		return (-1.0);
	t_res = t[0];
	if (t_res < 0)
		t_res = t[1];
	if (t_res < 0)
		return (-1.0);
	return (t_res);
}

double	check_cap(t_cylinder *cy, t_vec3 origin, t_vec3 dir, t_vec3 cap_center)
{
	t_obj	obj_plane;
	t_plane	plane;
	t_vec3	hit;
	t_vec3	dist_v;
	double	t;

	plane.point = cap_center;
	plane.normal = cy->normal;
	obj_plane.data = &plane;
	t = plane_intersect(&obj_plane, origin, dir);
	if (t > 0)
	{
		hit = vector_add(origin, vector_mult(dir, t));
		dist_v = vector_sub(hit, cap_center);
		if (vector_dot_product(dist_v, dist_v) <= cy->radius_sq)
			return (t);
	}
	return (-1.0);
}

double	cylinder_intersect(t_obj *this, t_vec3 origin, t_vec3 dir)
{
	t_cylinder	*cy;
	t_vec3		hit_point;
	t_vec3		half_height;
	double		t_pipe;
	double		t_bot;
	double		t_top;
	double		h;
	double		t;
	double		res;

	cy = (t_cylinder *)this->data;
	t_pipe = -1.0;
	t = pipe_intersect(cy, origin, dir);
	// oc = vector_sub(origin, cy->center);
	// d_dot = vector_dot_product(dir, cy->normal);
	// oc_dot = vector_dot_product(oc, cy->normal);
	// abc.x = vector_dot_product(dir, dir) - d_dot * d_dot;
	// abc.y = 2.0 * (vector_dot_product(dir, oc) - d_dot * oc_dot);
	// abc.z = vector_dot_product(oc, oc) - oc_dot * oc_dot - cy->radius_sq;
	// if (solve_quadratic(abc, &t[0], &t[1]) == NO)
	// 	return (-1.0);
	// t_res = t[0];
	// if (t_res < 0)
	// 	t_res = t[1];
	// if (t_res < 0)
	// 	return (-1.0);
	hit_point = vector_add(origin, vector_mult(dir, t));
	h = vector_dot_product(vector_sub(hit_point, cy->center), cy->normal);
	if (h >= -cy->height / 2.0 && h <= cy->height / 2.0)
		t_pipe = t;

	half_height = vector_mult(cy->normal, cy->height / 2.0);
	t_top = check_cap(cy, origin, dir, vector_add(cy->center, half_height));
	t_bot = check_cap(cy, origin, dir, vector_sub(cy->center, half_height));
	res = -1.0;
	if (t_pipe > 0)
		res = t_pipe;
	if (t_top > 0 && (res < 0 || t_top < res))
		res = t_top;
	if (t_bot > 0 && (res < 0 || t_bot < res))
		res = t_bot;
	return (res);
}

t_vtable	*get_cylinder_methods(void)
{
	static t_vtable	cylinder_methods;
	static int		is_init;

	if (!is_init)
	{
		cylinder_methods.get_normal = cylinder_get_normal;
		cylinder_methods.intersect = cylinder_intersect;
		cylinder_methods.get_type = cylinder_get_type;
		is_init = 1;
	}
	return (&cylinder_methods);
}

t_obj	*create_cylinder(t_vec3 pos, t_vec3 normal, double diametr,
		double height, t_color color, double reflection)
{
	t_obj		*obj;
	t_cylinder	*cylinder;

	obj = create_obj(color, reflection, DEFAULT_BRIGHTNESS);
	if (obj == NULL)
		return (HANDLE_ERROR_NULL);
	cylinder = malloc(sizeof(t_cylinder));
	if (cylinder == NULL)
		return (free(obj), HANDLE_ERROR_NULL);
	obj->methods = get_cylinder_methods();
	cylinder->center = pos;
	cylinder->normal = vector_norm(normal);
	cylinder->height = height;
	cylinder->radius = diametr / 2.0;
	cylinder->radius_sq = diametr * diametr / 4.0;
	obj->data = cylinder;
	return (obj);
}
