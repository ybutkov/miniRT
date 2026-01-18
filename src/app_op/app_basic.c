/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   app_basic.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybutkov <ybutkov@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/01 21:08:54 by ybutkov           #+#    #+#             */
/*   Updated: 2026/01/19 00:17:20 by ybutkov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "app_internal.h"
#include "colors.h"
#include "point.h"
#include "rays.h"

void	draw_map(t_app *app)
{
	t_point_2d	point;
	t_color		color_trace;
	t_ratio		ratio;
	t_ray		ray;

	point.y = 0;
	while (point.y < app->map->height)
	{
		point.x = 0;
		ratio.y = (double)(app->map->height - 1 - point.y) / (app->map->height
				- 1);
		while (point.x < app->map->width)
		{
			ratio.x = (double)point.x / (app->map->width - 1);
			ray = get_ray(app->map->camera, ratio.x, ratio.y);
			color_trace = trace_ray(ray, app->map, REFLECTION_AMOUNT);
			ft_mlx_pixel_put(app->img, point.x, point.y,
				color_to_int(color_trace));
			point.x++;
		}
		point.y++;
	}
}
