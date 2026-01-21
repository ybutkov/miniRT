/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_axes_labels.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybutkov <ybutkov@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/21 20:03:36 by ybutkov           #+#    #+#             */
/*   Updated: 2026/01/21 20:04:14 by ybutkov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "constants.h"
#include "map.h"
#include "miniRT.h"
#include "vectors.h"

void		project_axis(t_camera *cam, t_vec3 axis, int *screen_x,
				int *screen_y);
void		draw_camera_info(t_app *app);

static void	put_axis_labels(t_app *app)
{
	int	end_x;
	int	end_y;
	int	center_x;
	int	center_y;

	center_x = WINDOW_WIDTH - AXIS_OFFSET_X;
	center_y = AXIS_OFFSET_Y;
	project_axis(app->map->camera, create_vector(1, 0, 0), &end_x, &end_y);
	mlx_string_put(app->mlx, app->win, center_x + end_x + 5, center_y + end_y
		- 5, 0xFF0000, "X");
	project_axis(app->map->camera, create_vector(0, 1, 0), &end_x, &end_y);
	mlx_string_put(app->mlx, app->win, center_x + end_x + 5, center_y + end_y
		- 5, 0x00FF00, "Y");
	project_axis(app->map->camera, create_vector(0, 0, 1), &end_x, &end_y);
	mlx_string_put(app->mlx, app->win, center_x + end_x + 5, center_y + end_y
		- 5, 0x0000FF, "Z");
}

void	draw_axes_labels(t_app *app)
{
	if (!app->map || !app->map->camera)
		return ;
	put_axis_labels(app);
	draw_camera_info(app);
}
