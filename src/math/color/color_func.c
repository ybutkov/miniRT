/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color_func.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybutkov <ybutkov@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/14 19:47:47 by ybutkov           #+#    #+#             */
/*   Updated: 2026/01/15 22:29:28 by ybutkov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "colors.h"
#include "rays.h"
#include <math.h>

static t_color	get_bg_color_top(void)
{
	return (create_vector(0.1, 0.1, 0.2));
}

static t_color	get_bg_color_bottom(void)
{
	return (create_vector(0, 0, 0));
}

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
	color.r = (1.0 - t) * get_bg_color_bottom().r + t * get_bg_color_top().r;
	color.g = (1.0 - t) * get_bg_color_bottom().g + t * get_bg_color_top().g;
	color.b = (1.0 - t) * get_bg_color_bottom().b + t * get_bg_color_top().b;
	return (color);
}
