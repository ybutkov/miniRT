/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   miniRT.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybutkov <ybutkov@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/31 16:21:05 by ybutkov           #+#    #+#             */
/*   Updated: 2026/01/28 22:51:11 by ybutkov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "colors.h"
#include "constants.h"
#include "libft.h"
#include "map.h"
#include "miniRT.h"
#include "objects.h"
#include "parser.h"
#include "utils.h"
#include "vectors.h"
#include <mlx.h>
#include <stdio.h>
#include <stdlib.h>

static void	exit_program(t_map *map, char *message)
{
	if (map)
		map->free(map);
	perror(message);
	exit(EXIT_FAILURE);
}

static int	has_extension(const char *filename, const char *extension)
{
	size_t len;

	if (!filename)
		return (NO);
	len = ft_strlen(filename);
	if (len < 3)
		return (NO);
	return (ft_strcmp(&filename[len - 3], extension) == 0);
}

static int	loop_hook(t_app *app)
{
	long int	current_time;

	current_time = get_time_in_milliseconds();
	if ((current_time - app->last_frame_time < MIN_TIME_FRAMES)
		|| !app->map->is_change)
		return (0);
	app->render(app);
	return (0);
}

static t_app	*init_app(t_map *map, char *title)
{
	t_app	*app;

	app = create_app(map);
	if (!app)
		exit_program(map, "Error creating application");
	app->key_actions = init_key_actions();
	if (!app->key_actions)
		exit_program(map, "Error initializing key actions");
	app->mlx = map->mlx;
	app->win = mlx_new_window(app->mlx, app->width, app->height, title);
	app->img->img = mlx_new_image(app->mlx, app->width, app->height);
	app->img->addr = mlx_get_data_addr(app->img->img,
			&(app->img->bits_per_pixel), &(app->img->line_length),
			&(app->img->endian));
	mlx_hook(app->win, 17, 0, close_window, app);
	mlx_hook(app->win, 2, 1L << 0, key_pressed_hook, app);
	mlx_hook(app->win, 4, 1L << 2, ft_mouse_press, app);
	mlx_hook(app->win, 6, 1L << 6, ft_mouse_move, app);
	mlx_hook(app->win, 5, 1L << 3, ft_mouse_release, app);
	mlx_loop_hook(app->mlx, loop_hook, app);
	return (app);
}

int	main(int argc, char const *argv[])
{
	t_map	*map;
	t_app	*app;
	void	*mlx;

	(void)argv;
	if (argc != 2 || !has_extension(argv[1], ".rt"))
		exit_program(NULL, ERROR_MSG_ARGS);
	mlx = mlx_init();
	if (!mlx)
		exit_program(NULL, "Error initializing MLX");
	map = create_map(WINDOW_WIDTH, WINDOW_HEIGHT);
	map->mlx = mlx;
	parse_scene(argv[1], map);
	if (map->ambient == NULL || map->camera == NULL)
		exit_program(map, ERROR_MSG_PARAMS);
	printf("finish parsing\n");
	if (map->generate_bvh(map) == NO)
		exit_program(map, ERROR_MSG_BVH);
	app = init_app(map, "Wild World");
	mlx_loop(app->mlx);
	return (0);
}
