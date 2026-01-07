/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   app_basic.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybutkov <ybutkov@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/01 21:08:54 by ybutkov           #+#    #+#             */
/*   Updated: 2026/01/08 19:59:14 by ybutkov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "app_internal.h"
#include "rays.h"
#include "colors.h"

void	draw_map(t_app *app)
{
	int		x;
	int		y;
	t_color	color_trace;
	double	x_ratio;
	double	y_ratio;

	y = 0;
	while (y < app->map->height)
	{
		x = 0;
		while (x < app->map->width)
		{
			x_ratio = (double)x / (app->map->width - 1);
			y_ratio = (double)(app->map->height - 1 - y) / (app->map->height - 1);
			t_ray ray = get_ray(app->map->camera, x_ratio, y_ratio);
			color_trace = trace_ray(ray, app->map->objects, app->map, REFLECTION_AMOUNT);
			ft_mlx_pixel_put(app->img, x, y, color_to_int(color_trace));
			x++;
		}
		y++;
	}
}
