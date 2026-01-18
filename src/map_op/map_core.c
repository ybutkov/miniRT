/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_core.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybutkov <ybutkov@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/20 13:03:00 by ybutkov           #+#    #+#             */
/*   Updated: 2026/01/18 00:36:06 by ybutkov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "map_internal.h"
#include "miniRT.h"
#include "bvh.h"
#include "constants.h"
#include <math.h>

static void	free_map(t_map *map)
{
	free(map);
}

void	set_rotation(struct s_map *map, double x, double y, double z)
{
	map->rotation_x = x;
	map->rotation_y = y;
	map->rotation_z = z;
}

void	add_new_light(t_map *map, t_light *new_light)
{
	t_light	*cur;

	cur = map->lights;
	while (cur && cur->next)
		cur = cur->next;
	if (cur)
		cur->next = new_light;
	else
		map->lights = new_light;
}

void	add_new_object(t_map *map, t_obj *new_obj)
{
	t_obj	*cur;

	cur = map->objects;
	while(cur && cur->next)
		cur = cur->next;
	if (cur)
		cur->next = new_obj;
	else
		map->objects = new_obj;
}

static int	generate_bvh(t_map *map)
{
	t_bvh	*bvh;

	bvh = create_bvh();
	if (bvh == NULL)
		return (NO);
	if (bvh->build(bvh, map->objects) == NO)
		return (NO);
	map->bvh = bvh;
	return (OK);
}

t_map	*create_map(size_t width, size_t height)
{
	t_map	*map;

	if (width <= 0 || height <= 0)
		return (NULL);
	map = (t_map *)malloc(sizeof(t_map));
	if (!map)
		return (NULL);
	map->width = width;
	map->height = height;
	map->objects = NULL;
	map->shift_size = SHIFT_SIZE;
	map->zoom_size = ZOOM_SIZE_PERCENT;
	map->is_change = 1;
	map->free = free_map;
	map->reset = reset_map_transformations;
	map->shift = shift;
	map->zoom_in = zoom_in;
	map->add_light = add_new_light;
	map->add_obj = add_new_object;
	map->generate_bvh = generate_bvh;
	return (map);
}
