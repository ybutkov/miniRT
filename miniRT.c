/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   miniRT.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybutkov <ybutkov@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/31 16:21:05 by ybutkov           #+#    #+#             */
/*   Updated: 2026/01/08 19:59:34 by ybutkov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "map.h"
#include "miniRT.h"
#include "vectors.h"
#include "colors.h"
#include "utils.h"
#include "constants.h"
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
	app->mlx = mlx_init();
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

// int	main(int argc, char const *argv[])
// {
// 	t_map	*map;
// 	t_scene	scene;
// 	t_app	*app;

// 	(void)init_app;
// 	map = NULL;
// 	if (argc != 2)
// 		exit_program(NULL, ERROR_MSG_ARGS);
// 	init_scene(&scene);
// 	parse_scene(argv[1], &scene);
// 	print_scene(&scene);
// 	free_scene(&scene);
// 	// if (!map)
// 	// 	exit_program(NULL, "Error reading map from file");
// 	app = init_app(map, (char *)argv[1]);
// 	mlx_loop(app->mlx);
// 	return (0);
// }
void	add_test_objs_1(t_map *map)
{
	t_camera	camera;
	t_obj		*obj;
	t_vec3		pos;

	map->ambient = create_ambient(0.2, create_color(255, 255, 255));
	pos = create_vector(40, 50, 5);
	obj = create_sphere(pos, 10, create_color(255, 0, 0), REFLECTION_DEFAULT);
	map->objects = obj;
	pos = create_vector(20, 25, 2115);
	obj = create_sphere(pos, 2225, create_color(0, 0, 255), REFLECTION_DEFAULT);
	map->objects->next = obj;
	pos = create_vector(50, 45, 5);
	obj = create_sphere(pos, 15, create_color(0, 255, 0), REFLECTION_DEFAULT);
	map->objects->next->next = obj;

	map->lights = create_light(create_vector(-50, -100, -50),
			0.7, create_color(255, 255, 255));
	map->lights->next = create_light(create_vector(50, 100, -30),
			1.0, create_color(255, 255, 255));

	pos = create_vector(35, 35, -50);
	camera = create_camera(pos, create_vector(0.0, 0.0, 1.0), 70.0, map);
	map->camera = camera;
}

void	add_test_objs_2(t_map *map)
{
	t_camera	camera;
	t_obj		*obj;
	t_vec3		pos;

	map->ambient = create_ambient(0.1, create_color(255, 255, 255));

	obj = create_plane(create_vector(0, 0, 0), create_vector(0, 1, 0),
			create_color(150, 150, 150), 0.3);
	map->add_obj(map, obj);

	pos = create_vector(-5, 6, 10);
	obj = create_sphere(pos, 4, create_color(255, 255, 255), 1.0);
	map->add_obj(map, obj);

	pos = create_vector(5, 5, 5);
	obj = create_sphere(pos, 3, create_color(255, 0, 0), 0.0);
	map->add_obj(map, obj);

	// pos = create_vector(20, 15, 60);
	// obj = create_sphere(pos, 35, create_color(0, 0, 255));
	// obj1->next = obj;
	// obj1 = obj;

	map->add_light(map, create_light(create_vector(10, 20, -10),
			0.6, create_color(255, 255, 255)));
	map->add_light(map, create_light(create_vector(-15, 10, 5),
			0.2, create_color(255, 255, 255)));

	pos = create_vector(0, 5, -15);
	camera = create_camera(pos, create_vector(0, 0, 1), 70.0, map);
	map->camera = camera;

}

void	add_test_objs_3(t_map *map)
{
	t_camera	camera;
	t_obj		*obj;
	t_vec3		pos;

	map->ambient = create_ambient(0.1, create_color(255, 255, 255));

	obj = create_plane(create_vector(0, 20, 0), create_vector(-10, -10, 0),
			create_color(200, 200, 200), REFLECTION_DEFAULT);
	map->objects = obj;

	pos = create_vector(-10, 0, 50);
	obj = create_sphere(pos, 15, create_color(255, 0, 0), REFLECTION_DEFAULT);
	map->objects->next = obj;

	pos = create_vector(-20, 15, 50);
	obj = create_sphere(pos, 15, create_color(0, 255, 0), REFLECTION_DEFAULT);
	map->objects->next->next = obj;

	pos = create_vector(20, 15, 60);
	obj = create_sphere(pos, 35, create_color(0, 0, 255), REFLECTION_DEFAULT);
	map->objects->next->next->next = obj;

	pos = create_vector(0, 0, 0);
	obj = create_cylinder(pos, create_vector(0, 1, 0), 30, 50, 
		create_color(255, 0, 255), REFLECTION_DEFAULT);
	map->objects->next->next->next->next = obj;

	pos = create_vector(-150, 10, 20);
	obj = create_cylinder(pos, create_vector(1, 0, 0), 20, 40,
		create_color(155, 155, 155), REFLECTION_DEFAULT);
	map->objects->next->next->next->next->next = obj;

	pos = create_vector(-50, 45, 30);
	obj = create_sphere(pos, 20, create_color(200, 200, 0), REFLECTION_DEFAULT);
	map->objects->next->next->next->next->next->next = obj;

	obj = create_triangle(create_vector(-50, 30, 0), create_vector(-30, 30, -20),
		create_vector(-40, 40, 0), create_color(255, 155, 155), REFLECTION_DEFAULT);
	map->objects->next->next->next->next->next->next->next = obj;

	map->lights = create_light(create_vector(-50, -100, 20),
			0.8, create_color(255, 255, 255));
	map->lights->next = create_light(create_vector(-10, -50, -50),
			0.4, create_color(255, 255, 255));

	pos = create_vector(0, 0, -70);
	camera = create_camera(pos, create_vector(0, 0, 1), 70.0, map);
	map->camera = camera;

}

int	main(int argc, char const *argv[])
{
	t_map	*map;
	// t_scene	scene;
	t_app	*app;

	(void)init_app;
	(void)argc;
	(void)argv;
	map = create_map(WINDOW_WIDTH, WINDOW_HEIGHT);
	add_test_objs_2(map);
	app = init_app(map, (char *)argv[1]);
	mlx_loop(app->mlx);
	return (0);
}