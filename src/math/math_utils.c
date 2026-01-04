/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   math_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybutkov <ybutkov@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/04 18:34:56 by ybutkov           #+#    #+#             */
/*   Updated: 2026/01/04 21:44:15 by ybutkov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "constants.h"
#include "vectors.h"
#include <math.h>

int	solve_quadratic(t_vec3 abc, double *t1, double *t2)
{
	double	disc;
	double	sqrt_disc;

	disc = abc.y * abc.y - 4 * abc.x * abc.z;
	if (disc < 0)
		return (NO);
	sqrt_disc = sqrt(disc);
    // t1 has to be less then t2  check !!!
	*t1 = (-abc.y - sqrt_disc) / (2.0 * abc.x);
	*t2 = (-abc.y + sqrt_disc) / (2.0 * abc.x);
	return (OK);
}
