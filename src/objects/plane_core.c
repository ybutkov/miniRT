/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   plane_core.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybutkov <ybutkov@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/05 21:43:49 by ybutkov           #+#    #+#             */
/*   Updated: 2026/01/05 22:12:34 by ybutkov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "constants.h"
#include "objects.h"
#include <stdlib.h>
#include <math.h>

double	plane_intersect(t_obj *this, t_vec3 origin, t_vec3 dir)
{
	t_plane	*plane;
	t_vec3	p0_l0;
	double	denom;
	double	t;

	plane = (t_plane *)this->data;
	denom = vector_dot_product(plane->normal, dir);
	if (fabs(denom) > EPSILON)
	{
		p0_l0 = vector_sub(plane->point, origin);
		t = vector_dot_product(p0_l0, plane->normal) / denom;
		if (t >= 0)
			return (t);
	}
	return (-1.0);
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
		is_init = 1;
	}
	return (&plane_methods);
}

t_obj	*create_plane(t_vec3 point, t_vec3 normal, t_color color)
{
	t_obj	*obj;
	t_plane	*plane;

	obj = create_obj(color, DEFAULT_BRIGHTNESS);
	if (obj == NULL)
		return (HANDLE_ERROR_NULL);
	plane = malloc(sizeof(t_plane));
	if (plane == NULL)
		return (free(obj), HANDLE_ERROR_NULL);
	obj->methods = get_plane_methods();
	plane->point = point;
	plane->normal = normal;
	obj->data = plane;
	return (obj);
}
