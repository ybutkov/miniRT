/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   light_core.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybutkov <ybutkov@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/05 18:39:54 by ybutkov           #+#    #+#             */
/*   Updated: 2026/01/24 18:29:33 by ybutkov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "constants.h"
#include "objects.h"
#include "parser.h"
#include <stdlib.h>

t_light	*create_light(t_vec3 pos, double ratio, t_color color)
{
	t_light	*light;

	light = malloc(sizeof(t_light));
	if (light == NULL)
		return (HANDLE_ERROR_NULL);
	light->pos = pos;
	light->ratio = ratio;
	light->color = color;
	light->next = NULL;
	return (light);
}

int	create_l(t_data_rule rule, char **tokens, t_map *map)
{
	t_vec3	pos;
	float	ratio;
	t_color	color;
	t_light	*light;

	(void)rule;
	// check amount of tokens
	if (parser_vec3(tokens[1], &pos) == NO ||
		get_valid_float(tokens[2], &ratio) == NO)
		return (NO);
	if (tokens[3])
	{
		if (parser_color(tokens[3], &color) == NO)
			return (NO);
	}
	else
		color = create_color(255, 255, 255);
	light = create_light(pos, ratio, color);
	if (light == NULL)
		return (NO);
	map->add_light(map, light);
	return (OK);
}
