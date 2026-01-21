/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_internal.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybutkov <ybutkov@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/28 14:56:13 by ybutkov           #+#    #+#             */
/*   Updated: 2026/01/21 20:31:06 by ybutkov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAP_INTERNAL_H
# define MAP_INTERNAL_H

# include "map.h"
# include "point.h"

void		shift(t_map *map, int x, int y);
void		zoom_in(t_map *map, int percent);
void		reset_map_transformations(t_map *map);

#endif