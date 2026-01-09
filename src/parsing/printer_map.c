/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printer_map.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybutkov <ybutkov@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/01 18:22:08 by skomyshe          #+#    #+#             */
/*   Updated: 2026/01/09 13:59:07 by ybutkov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"
#include "map.h"
#include <stdio.h>
#include <stdlib.h>

void	print_map(t_map *map)
{
	int		index;
	t_obj	*obj;

	if (!map)
		return ;
	printf("===== Scene =====\n");
	if (map->camera)
		printf("Camera at (%f,%f,%f), FOV %d\n", map->camera->pos.x,
			map->camera->pos.y, map->camera->pos.z, map->camera->fov);
	if (map->ambient)
		printf("Ambient light: ratio %f, color (%f,%f,%f)\n",
			map->ambient->ratio, map->ambient->color.r,
			map->ambient->color.g, map->ambient->color.b);
	printf("\n===== Objects =====\n");
	obj = map->objects;
	index = 0;
	while (obj)
	{
		printf("Object %d:\n", index);
		printf("  Color: (%f, %f, %f)\n", obj->color.r, obj->color.g,
			obj->color.b);
		printf("  Brightness: %f\n", obj->brightness);
		printf("  Reflection: %f\n", obj->reflection);
		obj = obj->next;
		index++;
	}
	printf("\n===== Lights =====\n");
	if (map->lights)
		printf("Light at (%f,%f,%f), ratio %f\n", map->lights->pos.x,
			map->lights->pos.y, map->lights->pos.z, map->lights->ratio);
}
