/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color_func.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybutkov <ybutkov@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/14 19:47:47 by ybutkov           #+#    #+#             */
/*   Updated: 2026/01/25 20:45:47 by ybutkov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "colors.h"
#include "rays.h"
#include "map.h"
#include "objects.h"
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

t_color	get_background_color(t_ray ray, t_map *map)
{
	t_texture	*tex;
	double		u;
	double		v;
	double		theta;
	double		phi;

	if (!map || !map->background_texture)
		return (color_mix(get_bg_color_bottom(), get_bg_color_top(),
				0.5 * (ray.direction.y + 1.0)));
	tex = (t_texture *)map->background_texture;
	theta = acos(-ray.direction.y);
	phi = atan2(-ray.direction.z, ray.direction.x) + M_PI;
	u = phi / (2.0 * M_PI);
	v = theta / M_PI;
	return (get_texture_color(tex, u, v));
}
