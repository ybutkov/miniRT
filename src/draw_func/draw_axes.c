/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_axes.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybutkov <ybutkov@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/21 20:03:52 by ybutkov           #+#    #+#             */
/*   Updated: 2026/01/21 20:04:09 by ybutkov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "constants.h"
#include "draw_internal.h"
#include "map.h"
#include "miniRT.h"
#include "vectors.h"

void		draw_line_internal(t_line_draw *line);
void		draw_axes_labels(t_app *app);

void	project_axis(t_camera *cam, t_vec3 axis, int *screen_x, int *screen_y)
{
	double	x_proj;
	double	y_proj;

	x_proj = vector_dot_product(axis, cam->right);
	y_proj = vector_dot_product(axis, cam->up);
	*screen_x = (int)(x_proj * AXIS_LENGTH);
	*screen_y = (int)(-y_proj * AXIS_LENGTH);
}

static void	draw_axis_line(t_app *app, t_vec3 axis, int color)
{
	t_line_draw	line;
	int			end_x;
	int			end_y;
	int			center_x;
	int			center_y;

	center_x = WINDOW_WIDTH - AXIS_OFFSET_X;
	center_y = AXIS_OFFSET_Y;
	project_axis(app->map->camera, axis, &end_x, &end_y);
	line.img = app->img;
	line.x0 = center_x;
	line.y0 = center_y;
	line.x1 = center_x + end_x;
	line.y1 = center_y + end_y;
	line.color = color;
	draw_line_internal(&line);
}

void	draw_axes(t_app *app)
{
	if (!app->map || !app->map->camera)
		return ;
	draw_axis_line(app, create_vector(1, 0, 0), 0xFF0000);
	draw_axis_line(app, create_vector(0, 1, 0), 0x00FF00);
	draw_axis_line(app, create_vector(0, 0, 1), 0x0000FF);
	draw_axes_labels(app);
}
