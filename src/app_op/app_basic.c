/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   app_basic.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybutkov <ybutkov@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/01 21:08:54 by ybutkov           #+#    #+#             */
/*   Updated: 2026/01/18 00:12:31 by ybutkov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "app_internal.h"
#include "colors.h"
#include "rays.h"
#include "point.h"

void	draw_map(t_app *app)
{
	t_point_2d point;
	t_color	color_trace;
	double	x_ratio;
	double	y_ratio;
	t_ray	ray;

	point.y = 0;
	while (point.y < app->map->height)
	{
		point.x = 0;
		y_ratio = (double)(app->map->height - 1 - point.y) / (app->map->height - 1);
		while (point.x < app->map->width)
		{
			x_ratio = (double)point.x / (app->map->width - 1);
			ray = get_ray(app->map->camera, x_ratio, y_ratio);
			color_trace = trace_ray(ray, app->map, REFLECTION_AMOUNT);
			ft_mlx_pixel_put(app->img, point.x, point.y, color_to_int(color_trace));
			point.x++;
		}
		point.y++;
	}
}
