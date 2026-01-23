/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   miniRT.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybutkov <ybutkov@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/31 16:21:05 by ybutkov           #+#    #+#             */
/*   Updated: 2026/01/23 17:31:47 by ybutkov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "colors.h"
#include "constants.h"
#include "map.h"
#include "miniRT.h"
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
										&(app->img->bits_per_pixel),
										&(app->img->line_length),
										&(app->img->endian));
	mlx_hook(app->win, 17, 0, close_window, app);
	mlx_hook(app->win, 2, 1L << 0, key_pressed_hook, app);
	mlx_hook(app->win, 4, 1L << 2, ft_mouse_press, app);
	mlx_hook(app->win, 6, 1L << 6, ft_mouse_move, app);
	mlx_hook(app->win, 5, 1L << 3, ft_mouse_release, app);
	mlx_loop_hook(app->mlx, loop_hook, app);
	return (app);
}

#include "parser.h"
#include "libft.h"

void	add_test_objs_2(t_map *map)
{
	// t_camera		*camera;
	t_color_reflect	color_ref;
	t_obj			*obj;
	t_vec3			pos;

	// map->ambient = create_ambient(0.2, create_color(255, 255, 255));
	create_a(get_data_rule("A"), ft_split("A 0.8 255,255,255", ' '), map);
	
	obj = create_plane(create_vector(0, 0, 0), create_vector(0, 1, 0),
			create_color(150, 150, 150), 0.3);
	map->add_obj(map, obj);
	
	// 3 Spheres
	if (parser_vec3("-6,4,8", &pos) == 0)
		pos = create_vector(-6, 3, 8);
	t_color color;
	if (parser_color("-0,0,0", &color) == 1)
		obj = create_sphere(pos, 3, color, 0.4);
	else
		obj = create_sphere(pos, 3, create_color(255, 50, 50), 0.4);
	map->add_obj(map, obj);
	pos = create_vector(0, 2, 5);
	obj = create_sphere(pos, 2, create_color(50, 255, 50), 0.5);
	map->add_obj(map, obj);
	pos = create_vector(6, 2.5, 6);
	obj = create_sphere(pos, 2.5, create_color(50, 50, 255), 0.6);
	map->add_obj(map, obj);
	
	// 1 Box
	color_ref.color = create_color(255, 200, 50);
	color_ref.reflection = 0.4;
	obj = create_box(create_vector(2, 4, -2), create_vector(0, 1, 1),
			create_vector(3, 4, 3), color_ref);
	map->add_obj(map, obj);
	
	// Pyramid (6 triangles) - upside down with bigger base
	color_ref.color = create_color(200, 100, 255);
	color_ref.reflection = 0.3;
	pos = create_vector(8, 5, -3);
	// Base (now at top, bigger)
	obj = create_triangle(vector_add(pos, create_vector(-3, 0, -3)),
			vector_add(pos, create_vector(3, 0, -3)),
			vector_add(pos, create_vector(3, 0, 3)), color_ref);
	map->add_obj(map, obj);
	obj = create_triangle(vector_add(pos, create_vector(-3, 0, -3)),
			vector_add(pos, create_vector(3, 0, 3)),
			vector_add(pos, create_vector(-3, 0, 3)), color_ref);
	map->add_obj(map, obj);
	// Sides (pointing down)
	obj = create_triangle(vector_add(pos, create_vector(-3, 0, -3)),
			vector_add(pos, create_vector(3, 0, -3)),
			vector_add(pos, create_vector(0, -5, 0)), color_ref);
	map->add_obj(map, obj);
	obj = create_triangle(vector_add(pos, create_vector(3, 0, -3)),
			vector_add(pos, create_vector(3, 0, 3)),
			vector_add(pos, create_vector(0, -5, 0)), color_ref);
	map->add_obj(map, obj);
	obj = create_triangle(vector_add(pos, create_vector(3, 0, 3)),
			vector_add(pos, create_vector(-3, 0, 3)),
			vector_add(pos, create_vector(0, -5, 0)), color_ref);
	map->add_obj(map, obj);
	obj = create_triangle(vector_add(pos, create_vector(-3, 0, 3)),
			vector_add(pos, create_vector(-3, 0, -3)),
			vector_add(pos, create_vector(0, -5, 0)), color_ref);
	map->add_obj(map, obj);
	
	map->add_light(map, create_light(create_vector(10, 15, 0), 0.7,
				create_color(255, 255, 255)));
	map->add_light(map, create_light(create_vector(-10, 10, 5), 0.4,
				create_color(255, 255, 255)));
	
	create_c(get_data_rule("C"), ft_split("C 2,8,18 -0.5,0,-1 70.0", ' '), map);
	// pos = create_vector(12, 8, 18);
	// camera = create_camera(pos, create_vector(-0.5, 0, -1), 70.0, map);
	// map->camera = camera;
}

void	add_test_box(t_map *map)
{
	t_obj			*obj;
	t_color_reflect	color_ref;
	t_vec3			pos;
	double			diametr_height[2];

	// t_camera	*camera;
	// t_vec3		pos;
	// map->ambient = create_ambient(0.1, create_color(255, 255, 255));
	// obj = create_plane(create_vector(0, -10, 0), create_vector(0, 1, 0),
	// 		create_color(200, 200, 200), REFLECTION_DEFAULT);
	// map->objects = obj;
	color_ref.color = create_color(255, 0, 155);
	color_ref.reflection = 0.7;
	obj = create_box(create_vector(1, 2, -1), create_vector(1, 1, 1),
			create_vector(1.5, 1, 1), color_ref);
	map->add_obj(map, obj);
	// map->add_light(map, create_light(create_vector(10, 20, -10),
	// 		0.6, create_color(255, 255, 255)));
	// map->add_light(map, create_light(create_vector(-10, 20, -10),
	// 		0.6, create_color(255, 255, 255)));
	// camera = create_camera(create_vector(0, 0, -20),
	// 		create_vector(0, 0, 1), 70.0, map);
	// map->camera = camera;
	// pos = create_vector(10, 0, 5);
	// obj = create_sphere(pos, 4, create_color(0, 255, 255), 0.3);
	// map->add_obj(map, obj);
	pos = create_vector(5, 2, -2);
	diametr_height[0] = 3;
	diametr_height[1] = 6;
	color_ref.color = create_color(55, 55, 100);
	color_ref.reflection = 0.3;
	obj = create_cylinder(pos, create_vector(0, 1, 0), diametr_height,
			color_ref);
	map->add_obj(map, obj);
}

void	add_test_sphere(t_map *map)
{
	t_obj			*obj;
	t_vec3			pos;
	t_color_reflect	color_ref;
	double			diametr_height[2];

	pos = create_vector(-4, 0, 0);
	obj = create_sphere(pos, 5, create_color(255, 0, 0), 0.3);
	map->add_obj(map, obj);
	color_ref.color = create_color(0, 255, 0);
	color_ref.reflection = 0.2;
	obj = create_triangle(create_vector(-10, -5, -10), create_vector(10, -5,
				-10), create_vector(0, 10, -10), color_ref);
	map->add_obj(map, obj);
	pos = create_vector(5, 2, -2);
	diametr_height[0] = 3;
	diametr_height[1] = 4;
	color_ref.color = create_color(55, 55, 100);
	color_ref.reflection = 0.3;
	obj = create_cylinder(pos, create_vector(0, 1, 0), diametr_height,
			color_ref);
	map->add_obj(map, obj);
	color_ref.color = create_color(255, 0, 255);
	color_ref.reflection = 0.4;
	obj = create_box(create_vector(-4, 0, 3), create_vector(1, 1, 0),
			create_vector(3, 3, 3), color_ref);
	map->add_obj(map, obj);
	map->add_light(map, create_light(create_vector(10, 20, -10), 0.6,
				create_color(255, 255, 255)));
	// obj = create_triangle(create_vector(-8, 0, 15), create_vector(8, 0, 15),
	// 	create_vector(0, 8, 5), create_color(0, 0, 255), 0.4);
	// map->add_obj(map, obj);
}

int	main(int argc, char const *argv[])
{
	t_map *map;
	t_app *app;

	(void)argv;
	if (argc != 2)
		exit_program(NULL, "Error. There should be one argument - file name *.rt");
	map = create_map(WINDOW_WIDTH, WINDOW_HEIGHT);
	// add_test_box(map);
	add_test_objs_2(map);
	// parse_scene(argv[1], map);
	// add_test_box(map);
	printf("finish parsing\n");
	if (map->generate_bvh(map) == NO)
		exit_program(NULL, "PROBLEMS!!!");
	app = init_app(map, "Wild World");
	mlx_loop(app->mlx);
	return (0);
}