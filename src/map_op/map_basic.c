/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_basic.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybutkov <ybutkov@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/28 14:53:52 by ybutkov           #+#    #+#             */
/*   Updated: 2026/01/08 21:33:58 by ybutkov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "map_internal.h"
#include <math.h>

t_point	*get_point(t_map *map, int x, int y)
{
	if (!map || x >= map->width || y >= map->height)
		return (NULL);
	return (&map->points[y * map->width + x]);
}

void	set_point(t_map *map, int x, int y, t_point point)
{
	t_point	*target;

	if (!map || x >= map->width || y >= map->height)
		return ;
	target = &map->points[y * map->width + x];
	*target = point;
}

#include <stdio.h>
void	shift(t_map *map, int x, int y)
{
	rotate_camera(map->camera, create_vector(1, 0, 0), (double)y * 0.01);
	rotate_camera(map->camera, create_vector(0, 1, 0), (double)x * 0.01);
	update_camera(map->camera);
}

void	zoom_in(t_map *map, int delta)
{
	map->camera->fov = map->camera->fov  + delta;
	update_camera(map->camera);
}

double	normalize_angle(double angle)
{
	angle = fmod(angle, 2 * M_PI);
	if (angle > M_PI)
		angle -= 2 * M_PI;
	else if (angle < -M_PI)
		angle += 2 * M_PI;
	return (angle);
}
