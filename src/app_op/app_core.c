/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   app_core.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skomyshe <skomyshe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/01 21:24:59 by ybutkov           #+#    #+#             */
/*   Updated: 2026/01/05 21:49:20 by skomyshe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "app_internal.h"
#include "colors.h"
#include "miniRT.h"
#include "point.h"
#include "utils.h"

static void	render_map(t_app *app)
{
	app->clear_image(app->img);
	draw_map(app);
	// draw_info_panel(app);
	mlx_put_image_to_window(app->mlx, app->win, app->img->img, 0, 0);
	// print_info_panel(app);
	app->last_frame_time = get_time_in_milliseconds();
	app->map->is_change = 0;
}

static void	clear_image(t_img *img)
{
	int	bytes_per_pixel;
	int	image_size;
	int	i;

	bytes_per_pixel = img->bits_per_pixel / 8;
	image_size = img->line_length * WINDOW_HEIGHT;
	i = 0;
	// Do we need this ???
	while (i < image_size)
	{
		img->addr[i] = 0;
		img->addr[i + 1] = 0;
		img->addr[i + 2] = 0;
		if (bytes_per_pixel == 4)
			img->addr[i + 3] = 0;
		i += bytes_per_pixel;
	}
}

static void	free_app(t_app *app)
{
	static int	already_freed = 0;

	if (!app || already_freed)
		return ;
	already_freed = 1;
	if (app->img)
	{
		if (app->img->img)
			mlx_destroy_image(app->mlx, app->img->img);
		free(app->img);
	}
	if (app->win)
		mlx_destroy_window(app->mlx, app->win);
	if (app->map)
		app->map->free(app->map);
	if (app->mlx)
	{
		ft_mlx_destroy_display(app->mlx);
		free(app->mlx);
	}
	if (app->key_actions)
		app->key_actions->free(app->key_actions);
	free(app);
}

t_app	*create_app(t_map *map)
{
	t_app	*app;

	app = (t_app *)malloc(sizeof(t_app));
	if (!app)
		return (NULL);
	app->height = WINDOW_HEIGHT;
	app->width = WINDOW_WIDTH;
	app->img = (t_img *)malloc(sizeof(t_img));
	if (!app->img)
		return (NULL);
	app->mouse = (t_mouse_state){0, 0, 0, 0, 0, -1, -1};
	app->map = map;
	app->render = render_map;
	app->free = free_app;
	app->clear_image = clear_image;
	app->last_frame_time = get_time_in_milliseconds() - MIN_TIME_FRAMES - 1;
	return (app);
}
