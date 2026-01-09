/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sphere_core.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybutkov <ybutkov@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/04 17:49:55 by ybutkov           #+#    #+#             */
/*   Updated: 2026/01/09 14:28:04 by ybutkov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "constants.h"
#include "objects.h"
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

double	sphere_intersect(t_obj *this, t_vec3 origin, t_vec3 dir)
{
	t_sphere	*sphere;
	t_vec3		oc;
	t_vec3		abc;
	double		t[2];

	sphere = (t_sphere *)this->data;
	oc = vector_sub(origin, sphere->center);
	abc.x = vector_dot_product(dir, dir);
	abc.y = 2.0 * vector_dot_product(oc, dir);
	abc.z = vector_dot_product(oc, oc) - sphere->radius_sq;
	if (solve_quadratic(abc, &t[0], &t[1]) == NO)
		return (-1.0);
	if (t[0] > EPSILON)
		return (t[0]);
	if (t[1] > EPSILON)
		return (t[1]);
	return (-1.0);
}

t_vtable	*get_sphere_methods(void)
{
	static t_vtable	sphere_methods;
	static int		is_init;

	if (!is_init)
	{
		sphere_methods.get_normal = sphere_get_normal;
		sphere_methods.intersect = sphere_intersect;
		sphere_methods.get_type = sphere_get_type;
		is_init = 1;
	}
	return (&sphere_methods);
}

t_obj	*create_sphere(t_vec3 pos, double diametr, t_color color, double reflection)
{
	t_obj		*obj;
	t_sphere	*sphere;

	obj = create_obj(color, reflection, DEFAULT_BRIGHTNESS);
	if (obj == NULL)
		return (HANDLE_ERROR_NULL);
	sphere = malloc(sizeof(t_sphere));
	if (sphere == NULL)
		return (free(obj), HANDLE_ERROR_NULL);
	obj->methods = get_sphere_methods();
	sphere->center = pos;
	sphere->radius = diametr / 2.0;
	sphere->radius_sq = diametr * diametr / 4.0;
	obj->data = sphere;
	return (obj);
}
