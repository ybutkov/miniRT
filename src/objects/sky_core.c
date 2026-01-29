/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sky_core.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybutkov <ybutkov@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/25 20:24:44 by ybutkov           #+#    #+#             */
/*   Updated: 2026/01/29 14:29:15 by ybutkov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "constants.h"
#include "map.h"
#include "objects.h"
#include "parser.h"

// check amount of tokens and file existing
int	create_sky(t_data_rule rule, char **tokens, t_map *map)
{
	(void)rule;
	if (tokens[1]
		&& has_extension(tokens[1], ".xpm") == OK
		&& try_open_file(tokens[1]) == OK)
	{
		map->background_texture = load_texture(map->mlx, tokens[1]);
	}
	return (OK);
}
