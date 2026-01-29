/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_core_2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybutkov <ybutkov@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/02 17:58:17 by ybutkov           #+#    #+#             */
/*   Updated: 2026/01/29 15:36:05 by ybutkov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "map_internal.h"
#include "miniRT.h"
#include <math.h>

static void	free_objects(t_obj *obj, void *mlx)
{
	t_obj	*next;
	int		count;

	count = 0;
	while (obj)
	{
		next = obj->next;
		if (obj->data)
			free(obj->data);
		if (obj->texture)
		{
			if (obj->texture_type == TEXTURE_FILE)
				free_texture(mlx, (t_texture *)obj->texture);
			else if (obj->texture_type == TEXTURE_CHESS)
				free(obj->texture);
		}
		free(obj);
		count++;
		obj = next;
	}
}

static void	free_cameras(t_camera *camera)
{
	t_camera	*next;
	t_camera	*cur;

	cur = camera;
	while (cur)
	{
		if (cur->number)
			free(cur->number);
		next = cur->next;
		free(cur);
		cur = next;
		if (cur == camera)
			break ;
	}
}

static void	free_lights(t_light *light)
{
	t_light	*next;

	while (light)
	{
		next = light->next;
		free(light);
		light = next;
	}
}

void	free_map(t_map *map)
{
	if (!map)
		return ;
	if (!map->bvh && map->objects)
		free_objects(map->objects, map->mlx);
	if (map->lights)
		free_lights(map->lights);
	if (map->get_camera(map))
		free_cameras(map->get_camera(map));
	if (map->ambient)
		free(map->ambient);
	if (map->bvh)
		map->bvh->free(map->bvh);
	if (map->background_texture)
		free_texture(map->mlx, (t_texture *)map->background_texture);
	free(map);
}
