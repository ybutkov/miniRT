/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_core.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybutkov <ybutkov@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/03 21:36:28 by ybutkov           #+#    #+#             */
/*   Updated: 2026/01/03 21:46:36 by ybutkov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vectors.h"
#include "rays.h"

t_ray	create_ray(t_vec3 start, t_vec3 direction)
{
	t_ray	ray;

	ray.start = start;
	ray.direction = vector_norm(direction);
	return (ray);
}

t_vec3  ray_at_pos(t_ray ray, double pos)
{
	return (vector_add(ray.start, vector_mult(ray.direction, pos)));
}
