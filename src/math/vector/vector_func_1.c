/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector_func_1.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybutkov <ybutkov@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/14 19:52:07 by ybutkov           #+#    #+#             */
/*   Updated: 2026/01/14 19:52:09 by ybutkov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "vectors.h"
#include <math.h>

t_vec3	vector_add_scalar(t_vec3 v1, double sc)
{
	return (create_vector(v1.x + sc, v1.y + sc, v1.z + sc));
}

t_vec3	vector_sub_scalar(t_vec3 v1, double sc)
{
	return (vector_add_scalar(v1, -sc));
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
