/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sky_core.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybutkov <ybutkov@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/25 20:24:44 by ybutkov           #+#    #+#             */
/*   Updated: 2026/01/25 20:31:25 by ybutkov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "constants.h"
#include "map.h"
#include "objects.h"
#include "parser.h"


int	create_sky(t_data_rule rule, char **tokens, t_map *map)
{
	(void)rule;
	// check amount of tokens and file existing
	if (tokens[1])
	{
		map->background_texture = load_texture(map->mlx, tokens[1]);
	}
	return (OK);
}
