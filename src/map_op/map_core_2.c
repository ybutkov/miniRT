/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_core_2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybutkov <ybutkov@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/02 17:58:17 by ybutkov           #+#    #+#             */
/*   Updated: 2026/01/21 20:34:30 by ybutkov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "map_internal.h"
#include "miniRT.h"
#include <math.h>

static void	init_map_transformations(t_map *map)
{
	(void)map;
}

void	reset_map_transformations(t_map *map)
{
	init_map_transformations(map);
	map->is_change = 1;
}
