/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_axes.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybutkov <ybutkov@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/13 23:56:39 by ybutkov           #+#    #+#             */
/*   Updated: 2026/01/14 00:16:15 by ybutkov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"
#include "vectors.h"
#include <math.h>

#define AXIS_LENGTH 40
#define AXIS_OFFSET_X 80
#define AXIS_OFFSET_Y 80

static void	draw_line(t_img *img, int x0, int y0, int x1, int y1, int color)
{
	int	dx;
	int	dy;
	int	sx;
	int	sy;
	int	err;
	int	e2;

	dx = abs(x1 - x0);
	dy = abs(y1 - y0);
	sx = -1;
	if (x0 < x1)
		sx = 1;
	sy = -1;
	if (y0 < y1)
		sy = 1;
	err = dx - dy;
	while (1)
	{
		ft_mlx_pixel_put(img, x0, y0, color);
		if (x0 == x1 && y0 == y1)
			break ;
		e2 = 2 * err;
		if (e2 > -dy)
		{
			err -= dy;
			x0 += sx;
		}
		if (e2 < dx)
		{
			err += dx;
			y0 += sy;
		}
	}
}

static void	project_axis(t_camera *cam, t_vec3 axis, int *screen_x,
		int *screen_y)
{
	t_vec3	right_comp;
	t_vec3	up_comp;
	double	x_proj;
	double	y_proj;

	right_comp = vector_mult(cam->right, vector_dot_product(axis, cam->right));
	up_comp = vector_mult(cam->up, vector_dot_product(axis, cam->up));
	x_proj = vector_dot_product(axis, cam->right);
	y_proj = vector_dot_product(axis, cam->up);
	*screen_x = (int)(x_proj * AXIS_LENGTH);
	*screen_y = (int)(-y_proj * AXIS_LENGTH);
}

void	draw_axes(t_app *app)
{
	t_vec3	x_axis;
	t_vec3	y_axis;
	t_vec3	z_axis;
	int		center_x;
	int		center_y;
	int		end_x;
	int		end_y;

	if (!app->map || !app->map->camera)
		return ;
	center_x = WINDOW_WIDTH - AXIS_OFFSET_X;
	center_y = AXIS_OFFSET_Y;
	x_axis = create_vector(1, 0, 0);
	y_axis = create_vector(0, 1, 0);
	z_axis = create_vector(0, 0, 1);
	project_axis(app->map->camera, x_axis, &end_x, &end_y);
	draw_line(app->img, center_x, center_y, center_x + end_x, center_y + end_y,
			0xFF0000);
	project_axis(app->map->camera, y_axis, &end_x, &end_y);
	draw_line(app->img, center_x, center_y, center_x + end_x, center_y + end_y,
			0x00FF00);
	project_axis(app->map->camera, z_axis, &end_x, &end_y);
	draw_line(app->img, center_x, center_y, center_x + end_x, center_y + end_y,
			0x0000FF);
}

void	draw_axes_labels(t_app *app)
{
	t_vec3	x_axis;
	t_vec3	y_axis;
	t_vec3	z_axis;
	int		center_x;
	int		center_y;
	int		end_x;
	int		end_y;
	char	*str;
	int		base_x;
	int		base_y;

	if (!app->map || !app->map->camera)
		return ;
	center_x = WINDOW_WIDTH - AXIS_OFFSET_X;
	center_y = AXIS_OFFSET_Y;
	x_axis = create_vector(1, 0, 0);
	y_axis = create_vector(0, 1, 0);
	z_axis = create_vector(0, 0, 1);
	project_axis(app->map->camera, x_axis, &end_x, &end_y);
	mlx_string_put(app->mlx, app->win, center_x + end_x + 5, center_y + end_y
			- 5, 0xFF0000, "X");
	project_axis(app->map->camera, y_axis, &end_x, &end_y);
	mlx_string_put(app->mlx, app->win, center_x + end_x + 5, center_y + end_y
			- 5, 0x00FF00, "Y");
	project_axis(app->map->camera, z_axis, &end_x, &end_y);
	mlx_string_put(app->mlx, app->win, center_x + end_x + 5, center_y + end_y
			- 5, 0x0000FF, "Z");
	base_x = center_x - 60;
	base_y = center_y + 55;
	mlx_string_put(app->mlx, app->win, base_x, base_y, 0xFFFFFF, "Camera");
	mlx_string_put(app->mlx, app->win, base_x + 40, base_y + 15, 0xFFFFFF,
			"Pos");
	mlx_string_put(app->mlx, app->win, base_x + 100, base_y + 15, 0xFFFFFF,
			"Dir");
	mlx_string_put(app->mlx, app->win, base_x, base_y + 30, 0xFFFFFF, "X");
	str = ft_double_to_str(app->map->camera->pos.x, 1);
	mlx_string_put(app->mlx, app->win, base_x + 40, base_y + 30, 0xFFFFFF,
			str);
	free(str);
	str = ft_double_to_str(app->map->camera->dir.x, 2);
	mlx_string_put(app->mlx, app->win, base_x + 100, base_y + 30, 0xFFFFFF,
			str);
	free(str);
	mlx_string_put(app->mlx, app->win, base_x, base_y + 45, 0xFFFFFF, "Y");
	str = ft_double_to_str(app->map->camera->pos.y, 1);
	mlx_string_put(app->mlx, app->win, base_x + 40, base_y + 45, 0xFFFFFF,
			str);
	free(str);
	str = ft_double_to_str(app->map->camera->dir.y, 2);
	mlx_string_put(app->mlx, app->win, base_x + 100, base_y + 45, 0xFFFFFF,
			str);
	free(str);
	mlx_string_put(app->mlx, app->win, base_x, base_y + 60, 0xFFFFFF, "Z");
	str = ft_double_to_str(app->map->camera->pos.z, 1);
	mlx_string_put(app->mlx, app->win, base_x + 40, base_y + 60, 0xFFFFFF,
			str);
	free(str);
	str = ft_double_to_str(app->map->camera->dir.z, 2);
	mlx_string_put(app->mlx, app->win, base_x + 100, base_y + 60, 0xFFFFFF,
			str);
	free(str);
}

