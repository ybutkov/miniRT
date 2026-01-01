/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_elements.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skomyshe <skomyshe@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/31 21:40:24 by skomyshe          #+#    #+#             */
/*   Updated: 2026/01/01 21:49:11 by skomyshe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

// Ambient A

void	parse_ambient(char **tokens, t_scene *scene)
{
	if (scene->ambient)
		error_exit("Ambient already defined");
	if (ft_split_len(tokens) != 3)
		error_exit("Invalid ambient format");
	scene->ambient = malloc(sizeof(t_ambient));
	scene->ambient->ratio = ft_atof(tokens[1]);
	scene->ambient->color = parse_color(tokens[2]);
	if (scene->ambient->ratio < 0.0 || scene->ambient->ratio > 1.0)
		error_exit("Ambient ratio out of range");
}

// camera C
void	parse_camera(char **tokens, t_scene *scene)
{
	if (scene->camera)
		error_exit("Camera already defined");
	if (ft_split_len(tokens) != 4)
		error_exit("Invalid camera format");
	scene->camera = malloc(sizeof(t_camera));
	scene->camera->pos = parse_vec3(tokens[1]);
	scene->camera->dir = parse_vec3(tokens[2]);
	scene->camera->fov = ft_atoi(tokens[3]);
	check_normalized(scene->camera->dir);
	if (scene->camera->fov < 0 || scene->camera->fov > 180)
		error_exit("Invalid FOV");
}

// Light L
void	parse_light(char **tokens, t_scene *scene)
{
	if (scene->light)
		error_exit("Light already defined");
	if (ft_split_len(tokens) < 3)
		error_exit("Invalid light format");
	scene->light = malloc(sizeof(t_light));
	scene->light->pos = parse_vec3(tokens[1]);
	scene->light->ratio = ft_atof(tokens[2]);
	scene->light->color = parse_color(tokens[3]);
	if (scene->light->ratio < 0.0 || scene->light->ratio > 1.0)
		error_exit("Light ratio out of range");
}

// Sphere
void	parse_sphere(char **tokens, t_scene *scene)
{
	t_object	*obj;

	if (ft_split_len(tokens) != 4)
		error_exit("Invalid sphere format");
	obj = malloc(sizeof(t_object));
	obj->type = SPHERE;
	obj->pos = parse_vec3(tokens[1]);
	obj->diameter = ft_atof(tokens[2]);
	obj->color = parse_color(tokens[3]);
	if (obj->diameter <= 0)
		error_exit("Invalid sphere diameter");
	obj->next = scene->objects;
	scene->objects = obj;
}

// Plane
void	parse_plane(char **tokens, t_scene *scene)
{
	t_object	*obj;

	if (ft_split_len(tokens) != 4)
		error_exit("Invalid plane format");
	obj = malloc(sizeof(t_object));
	obj->type = PLANE;
	obj->pos = parse_vec3(tokens[1]);
	obj->dir = parse_vec3(tokens[2]);
	obj->color = parse_color(tokens[3]);
	check_normalized(obj->dir);
	obj->next = scene->objects;
	scene->objects = obj;
}

// Cylinder cy
void	parse_cylinder(char **tokens, t_scene *scene)
{
	t_object	*obj;

	if (ft_split_len(tokens) != 6)
		error_exit("Invalid cylinder format");
	obj = malloc(sizeof(t_object));
	obj->type = CYLINDER;
	obj->pos = parse_vec3(tokens[1]);
	obj->dir = parse_vec3(tokens[2]);
	obj->diameter = ft_atof(tokens[3]);
	obj->height = ft_atof(tokens[4]);
	obj->color = parse_color(tokens[5]);
	check_normalized(obj->dir);
	if (obj->diameter <= 0 || obj->height <= 0)
		error_exit("Invalid cylinder dimensions");
	obj->next = scene->objects;
	scene->objects = obj;
}
