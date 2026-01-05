/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_basic.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybutkov <ybutkov@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/28 14:53:52 by ybutkov           #+#    #+#             */
/*   Updated: 2026/01/05 18:20:17 by ybutkov          ###   ########.fr       */
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
	map->offset_x += x;
	map->offset_y += y;
	//
	map->camera.pos = vector_sub(map->camera.pos, create_vector((double)x, (double)y, 0.0));
	update_camera(&map->camera);
}

void	zoom_in(t_map *map, int percent)
{
	// if (percent == 0)
	// 	return ;
	// map->zoom *= (1.0 + percent / 100.0);
	// if (map->zoom < 1.0)
	// 	map->zoom = 1.0;
	// change from percent to shift
	map->camera.pos = vector_sub(map->camera.pos, create_vector(0.0, 0.0, (double)percent));
	printf("%f %f %f\n", map->camera.pos.x, map->camera.pos.y, map->camera.pos.z);
	fflush(stdout);
	update_camera(&map->camera);
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
