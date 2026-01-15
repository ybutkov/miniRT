/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color_func.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybutkov <ybutkov@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/14 19:47:47 by ybutkov           #+#    #+#             */
/*   Updated: 2026/01/14 19:47:49 by ybutkov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "colors.h"
#include "rays.h"
#include <math.h>

t_color	color_product(t_color c1, t_color c2)
{
	t_color	color;

	color.r = c1.r * c2.r;
	color.g = c1.g * c2.g;
	color.b = c1.b * c2.b;
	return (color);
}

t_color	get_background_color(t_ray ray)
{
	t_color	color;
	double	t;

	t = 0.5 * (ray.direction.y + 1.0);
	color.r = (1.0 - t) * BG_COLOR_BOTTOM.r + t * BG_COLOR_TOP.r;
	color.g = (1.0 - t) * BG_COLOR_BOTTOM.g + t * BG_COLOR_TOP.g;
	color.b = (1.0 - t) * BG_COLOR_BOTTOM.b + t * BG_COLOR_TOP.b;
	return (color);
}
