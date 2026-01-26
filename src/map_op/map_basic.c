/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_basic.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybutkov <ybutkov@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/28 14:53:52 by ybutkov           #+#    #+#             */
/*   Updated: 2026/01/26 18:51:04 by ybutkov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "map_internal.h"
#include <math.h>

void	shift(t_map *map, int x, int y)
{
	rotate_camera(map->camera, create_vector(1, 0, 0), (double)y * 0.01);
	rotate_camera(map->camera, create_vector(0, 1, 0), (double)x * 0.01);
	update_camera(map->camera);
}

void	zoom_in(t_map *map, int delta)
{
	map->camera->update_fov(map->camera, delta);
	update_camera(map->camera);
}
