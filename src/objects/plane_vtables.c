/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   plane_vtables.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybutkov <ybutkov@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/25 23:29:59 by ybutkov           #+#    #+#             */
/*   Updated: 2026/01/25 23:31:37 by ybutkov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "obj_internal.h"

t_obj_type	plane_get_type(void)
{
	return (PLANE);
}

t_vec3	plane_get_normal(t_obj *this, t_vec3 pos)
{
	t_plane	*plane;

	(void)pos;
	plane = (t_plane *)this->data;
	return (vector_norm(plane->normal));
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
		plane_methods.get_color = default_get_color;
		is_init = 1;
	}
	return (&plane_methods);
}
