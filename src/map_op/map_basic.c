/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_basic.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybutkov <ybutkov@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/28 14:53:52 by ybutkov           #+#    #+#             */
/*   Updated: 2026/01/29 02:00:56 by ybutkov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "map_internal.h"
#include <math.h>

void	shift(t_map *map, int x, int y)
{
	rotate_camera(map->get_camera(map), create_vector(1, 0, 0),
		(double)y * 0.01);
	rotate_camera(map->get_camera(map), create_vector(0, 1, 0),
		(double)x * 0.01);
	update_camera(map->get_camera(map));
}

void	zoom_in(t_map *map, int delta)
{
	map->get_camera(map)->update_fov(map->get_camera(map), delta);
	update_camera(map->get_camera(map));
}

void	add_camera(t_map *map, t_camera *camera)
{
	t_camera	*cur;

	cur = map->get_camera(map);
	while (cur && cur->next)
		cur = cur->next;
	if (cur)
		cur->next = camera;
	else
		map->camera = camera;
}

t_camera	*get_current_camera(t_map *map)
{
	return (map->camera);
}

void	finish_preparation(t_map *map)
{
	t_camera	*cur;

	cur = map->get_camera(map);
	while (cur && cur->next)
		cur = cur->next;
	cur->next = map->camera;
}
