/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_axes_info.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybutkov <ybutkov@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/21 20:05:24 by ybutkov           #+#    #+#             */
/*   Updated: 2026/01/21 20:05:31 by ybutkov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "constants.h"
#include "draw_internal.h"
#include "map.h"
#include "miniRT.h"
#include "vectors.h"

static void	put_coord_str(t_app *app, double value, t_coord_info *info)
{
	char	*str;

	str = ft_double_to_str(value, info->decimals);
	mlx_string_put(app->mlx, app->win, info->x, info->y, 0xFFFFFF, str);
	free(str);
}

static void	put_x_info(t_app *app, int base_x, int base_y)
{
	t_coord_info	info;

	mlx_string_put(app->mlx, app->win, base_x, base_y + 30, 0xFFFFFF, "X");
	info.x = base_x + 40;
	info.y = base_y + 30;
	info.decimals = 1;
	put_coord_str(app, app->map->camera->pos.x, &info);
	info.x = base_x + 100;
	info.decimals = 2;
	put_coord_str(app, app->map->camera->dir.x, &info);
}

static void	put_y_info(t_app *app, int base_x, int base_y)
{
	t_coord_info	info;

	mlx_string_put(app->mlx, app->win, base_x, base_y + 45, 0xFFFFFF, "Y");
	info.x = base_x + 40;
	info.y = base_y + 45;
	info.decimals = 1;
	put_coord_str(app, app->map->camera->pos.y, &info);
	info.x = base_x + 100;
	info.decimals = 2;
	put_coord_str(app, app->map->camera->dir.y, &info);
}

static void	put_z_info(t_app *app, int base_x, int base_y)
{
	t_coord_info	info;

	mlx_string_put(app->mlx, app->win, base_x, base_y + 60, 0xFFFFFF, "Z");
	info.x = base_x + 40;
	info.y = base_y + 60;
	info.decimals = 1;
	put_coord_str(app, app->map->camera->pos.z, &info);
	info.x = base_x + 100;
	info.decimals = 2;
	put_coord_str(app, app->map->camera->dir.z, &info);
}

void	draw_camera_info(t_app *app)
{
	int	center_x;
	int	center_y;
	int	base_x;
	int	base_y;

	center_x = WINDOW_WIDTH - AXIS_OFFSET_X;
	center_y = AXIS_OFFSET_Y;
	base_x = center_x - 60;
	base_y = center_y + 55;
	mlx_string_put(app->mlx, app->win, base_x, base_y, 0xFFFFFF, "Camera");
	mlx_string_put(app->mlx, app->win, base_x + 40, base_y + 15, 0xFFFFFF,
		"Pos");
	mlx_string_put(app->mlx, app->win, base_x + 100, base_y + 15, 0xFFFFFF,
		"Dir");
	put_x_info(app, base_x, base_y);
	put_y_info(app, base_x, base_y);
	put_z_info(app, base_x, base_y);
}
