/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color_core.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybutkov <ybutkov@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/02 23:20:16 by ybutkov           #+#    #+#             */
/*   Updated: 2026/01/04 21:19:37 by ybutkov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "colors.h"
#include "rays.h"
#include <math.h>

int	color_to_int(t_color color)
{
	int	r;
	int	g;
	int	b;

	r = (int)(fmin(1.0, fmax(0.0, color.r)) * 255.999);
	g = (int)(fmin(1.0, fmax(0.0, color.g)) * 255.999);
	b = (int)(fmin(1.0, fmax(0.0, color.b)) * 255.999);
	return (r << 16 | g << 8 | b);
}

t_color	color_mix(t_color c1, t_color c2, double intensity)
{
	t_color	color;

	color.r = c1.r * c2.r * intensity;
	color.g = c1.g * c2.g * intensity;
	color.b = c1.b * c2.b * intensity;
	return (color);
}

t_color	color_mult(t_color c1, double scalar)
{
	t_color	color;

	color.r = c1.r * scalar;
	color.g = c1.g * scalar;
	color.b = c1.b * scalar;
	return (color);
}

t_color	color_add(t_color c1, t_color c2)
{
	t_color	color;

	color.r = c1.r + c2.r;
	color.g = c1.g + c2.g;
	color.b = c1.b + c2.b;
	return (color);
}

t_color	create_color(int r, int g, int b)
{
	t_color	color;

	color.r = (double)r / 255.0;
	color.g = (double)g / 255.0;
	color.b = (double)b / 255.0;
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
