/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector_func_2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybutkov <ybutkov@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/03 19:28:04 by ybutkov           #+#    #+#             */
/*   Updated: 2026/01/14 19:53:30 by ybutkov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "vectors.h"
#include <math.h>

t_vec3	vector_cross(t_vec3 v1, t_vec3 v2)
{
	t_vec3	vector;

	vector.x = v1.y * v2.z - v1.z * v2.y;
	vector.y = v1.z * v2.x - v1.x * v2.z;
	vector.z = v1.x * v2.y - v1.y * v2.x;
	return (vector);
}

t_vec3	vector_reflect(t_vec3 ray, t_vec3 normal)
{
	double	dot;

	dot = vector_dot_product(ray, normal);
	return (vector_sub(ray, vector_mult(normal, 2.0 * dot)));
}

t_vec3	vector_rotate_axis(t_vec3 v, t_vec3 axis, double angle)
{
	t_vec3	res;
	double	cos_angle;
	double	sin_angle;

	cos_angle = cos(angle);
	sin_angle = sin(angle);
	axis = vector_norm(axis);
	res = vector_mult(v, cos_angle);
	res = vector_add(res, vector_mult(vector_cross(axis, v), sin_angle));
	res = vector_add(res, vector_mult(axis, vector_dot_product(axis, v) * (1.0
					- cos_angle)));
	return (res);
}

t_vec3	vector_min(t_vec3 v1, t_vec3 v2)
{
	t_vec3	vector;

	vector.x = fmin(v1.x, v2.x);
	vector.y = fmin(v1.y, v2.y);
	vector.z = fmin(v1.z, v2.z);
	return (vector);
}

t_vec3	vector_max(t_vec3 v1, t_vec3 v2)
{
	t_vec3	vector;

	vector.x = fmax(v1.x, v2.x);
	vector.y = fmax(v1.y, v2.y);
	vector.z = fmax(v1.z, v2.z);
	return (vector);
}
