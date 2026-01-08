/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector_core.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybutkov <ybutkov@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/03 19:28:04 by ybutkov           #+#    #+#             */
/*   Updated: 2026/01/08 15:39:51 by ybutkov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "vectors.h"
#include <math.h>

t_vec3	vector_add(t_vec3 v1, t_vec3 v2)
{
	t_vec3	vector;

	vector.x = v1.x + v2.x;
	vector.y = v1.y + v2.y;
	vector.z = v1.z + v2.z;
	return (vector);
}

t_vec3	vector_sub(t_vec3 v1, t_vec3 v2)
{
	t_vec3	vector;

	vector.x = v1.x - v2.x;
	vector.y = v1.y - v2.y;
	vector.z = v1.z - v2.z;
	return (vector);
}

t_vec3	vector_mult(t_vec3 v1, double scalar)
{
	t_vec3	vector;

	vector.x = v1.x * scalar;
	vector.y = v1.y * scalar;
	vector.z = v1.z * scalar;
	return (vector);
}

double	vector_dot_product(t_vec3 v1, t_vec3 v2)
{
	return (v1.x * v2.x + v1.y * v2.y + v1.z * v2.z);
}

double	vector_length(t_vec3 v1)
{
	return (sqrt(v1.x * v1.x + v1.y * v1.y + v1.z * v1.z));
}

t_vec3	vector_norm(t_vec3 v1)
{
	t_vec3	vector;
	double	len;

	len = vector_length(v1);
	if (len == 0)
		return (create_vector(0, 0, 0));
	vector.x = v1.x / len;
	vector.y = v1.y / len;
	vector.z = v1.z / len;
	return (vector);
}

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

t_vec3	create_vector(double x, double y, double z)
{
	t_vec3	vector;

	vector.x = x;
	vector.y = y;
	vector.z = z;
	return (vector);
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
	res = vector_add(res, vector_mult(axis, 
		vector_dot_product(axis, v) * (1.0 - cos_angle)));
	return (res);
}
