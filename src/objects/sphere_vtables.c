/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sphere_vtables.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybutkov <ybutkov@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/25 23:33:43 by ybutkov           #+#    #+#             */
/*   Updated: 2026/01/25 23:36:51 by ybutkov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "constants.h"
#include "obj_internal.h"
#include "parser.h"
#include "vectors.h"
#include <stdlib.h>

t_obj_type	sphere_get_type(void)
{
	return (SPHERE);
}

t_vec3	sphere_get_normal(t_obj *this, t_vec3 pos)
{
	t_sphere	*sphere;
	t_vec3		normal;

	sphere = (t_sphere *)this->data;
	normal = vector_sub(pos, sphere->center);
	return (vector_norm(normal));
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
		sphere_methods.get_color = sphere_get_color;
		is_init = 1;
	}
	return (&sphere_methods);
}
