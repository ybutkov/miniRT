/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector_core.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybutkov <ybutkov@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/03 19:28:04 by ybutkov           #+#    #+#             */
/*   Updated: 2026/01/03 19:49:16 by ybutkov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "vectors.h"

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

	ft_memset(&vector, 0, sizeof(t_vec3));
	len = vector_length(v1);
	if (len == 0)
		return (vector);
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

t_vec3	create_vector(double x, double y, double z)
{
	t_vec3	vector;

	vector.x = x;
	vector.y = y;
	vector.z = z;
	return (vector);
}