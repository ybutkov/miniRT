/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector_core.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybutkov <ybutkov@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/03 19:28:04 by ybutkov           #+#    #+#             */
/*   Updated: 2026/01/15 22:14:34 by ybutkov          ###   ########.fr       */
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

t_vec3	create_vector(double x, double y, double z)
{
	t_vec3	vector;

	vector.x = x;
	vector.y = y;
	vector.z = z;
	return (vector);
}
