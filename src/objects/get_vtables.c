/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_vtables.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybutkov <ybutkov@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/15 15:46:38 by ybutkov           #+#    #+#             */
/*   Updated: 2026/01/15 21:53:11 by ybutkov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "obj_internal.h"

t_vtable	*get_box_methods(void)
{
	static t_vtable	box_methods;
	static int		is_init;

	if (!is_init)
	{
		box_methods.get_normal = box_get_normal;
		box_methods.intersect = box_intersect;
		box_methods.get_aabb = box_get_aabb;
		box_methods.get_type = box_get_type;
		is_init = 1;
	}
	return (&box_methods);
}

t_vtable	*get_cylinder_methods(void)
{
	static t_vtable	cylinder_methods;
	static int		is_init;

	if (!is_init)
	{
		cylinder_methods.get_normal = cylinder_get_normal;
		cylinder_methods.intersect = cylinder_intersect;
		cylinder_methods.get_aabb = cylinder_get_aabb;
		cylinder_methods.get_type = cylinder_get_type;
		is_init = 1;
	}
	return (&cylinder_methods);
}

t_vtable	*get_plane_methods(void)
{
	static t_vtable	plane_methods;
	static int		is_init;

	if (!is_init)
	{
		plane_methods.get_normal = plane_get_normal;
		plane_methods.intersect = plane_intersect;
		plane_methods.get_aabb = plane_get_aabb;
		plane_methods.get_type = plane_get_type;
		is_init = 1;
	}
	return (&plane_methods);
}

t_vtable	*get_sphere_methods(void)
{
	static t_vtable	sphere_methods;
	static int		is_init;

	if (!is_init)
	{
		sphere_methods.get_normal = sphere_get_normal;
		sphere_methods.intersect = sphere_intersect;
		sphere_methods.get_aabb = sphere_get_aabb;
		sphere_methods.get_type = sphere_get_type;
		is_init = 1;
	}
	return (&sphere_methods);
}

t_vtable	*get_triangle_methods(void)
{
	static t_vtable	triangle_methods;
	static int		is_init;

	if (!is_init)
	{
		triangle_methods.get_normal = triangle_get_normal;
		triangle_methods.intersect = triangle_intersect;
		triangle_methods.get_aabb = triangle_get_aabb;
		triangle_methods.get_type = triangle_get_type;
		is_init = 1;
	}
	return (&triangle_methods);
}
