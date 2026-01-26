/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   triangle_vtables.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybutkov <ybutkov@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/25 23:38:26 by ybutkov           #+#    #+#             */
/*   Updated: 2026/01/25 23:39:10 by ybutkov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "obj_internal.h"
#include "constants.h"
#include <math.h>

t_vec3	triangle_get_normal(t_obj *this, t_vec3 pos)
{
	t_triangle	*triangle;

	(void)pos;
	triangle = (t_triangle *)this->data;
	return (triangle->normal);
}

t_obj_type	triangle_get_type(void)
{
	return (TRIANGLE);
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
		triangle_methods.get_color = default_get_color;
		is_init = 1;
	}
	return (&triangle_methods);
}
