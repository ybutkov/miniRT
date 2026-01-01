/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scene.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skomyshe <skomyshe@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/01 18:22:08 by skomyshe          #+#    #+#             */
/*   Updated: 2026/01/01 21:59:47 by skomyshe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"
#include <stdio.h>
#include <stdlib.h>

void	init_scene(t_scene *scene)
{
	if (!scene)
		return ;
	scene->ambient = NULL;
	scene->camera = NULL;
	scene->light = NULL;
	scene->objects = NULL;
}

void	print_scene(t_scene *scene)
{
	int			sphere;
	t_object	*obj;

	sphere = 0, plane;
	sphere = 0, plane = 0, cylinder;
	if (!scene)
		return ;
	printf("===== Scene =====\n");
	if (scene->camera)
		printf("Camera at (%f,%f,%f), FOV %d\n", scene->camera->pos.x,
			scene->camera->pos.y, scene->camera->pos.z, scene->camera->fov);
	if (scene->ambient)
		printf("Ambient light: ratio %f, color (%d,%d,%d)\n",
			scene->ambient->ratio, scene->ambient->color.r,
			scene->ambient->color.g, scene->ambient->color.b);
	sphere = 0, plane = 0, cylinder = 0;
	obj = scene->objects;
	while (obj)
	{
		if (obj->type == SPHERE)
			sphere++;
		else if (obj->type == PLANE)
			plane++;
		else if (obj->type == CYLINDER)
			cylinder++;
		obj = obj->next;
	}
	printf("Objects: %d spheres, %d planes, %d cylinders\n", sphere, plane,
		cylinder);
	if (scene->light)
		printf("Light at (%f,%f,%f), ratio %f\n", scene->light->pos.x,
			scene->light->pos.y, scene->light->pos.z, scene->light->ratio);
}

void	free_scene(t_scene *scene)
{
	t_object	*obj;
	t_object	*tmp;

	if (!scene)
		return ;
	// Ambient
	if (scene->ambient)
		free(scene->ambient);
	// Camera
	if (scene->camera)
		free(scene->camera);
	// Light
	if (scene->light)
		free(scene->light);
	// Objects
	obj = scene->objects;
	while (obj)
	{
		tmp = obj->next;
		free(obj);
		obj = tmp;
	}
	// Reset pointers
	scene->ambient = NULL;
	scene->camera = NULL;
	scene->light = NULL;
	scene->objects = NULL;
}
