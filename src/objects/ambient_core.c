/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ambient_core.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybutkov <ybutkov@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/05 20:10:10 by ybutkov           #+#    #+#             */
/*   Updated: 2026/01/28 22:13:40 by ybutkov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "objects.h"
#include "constants.h"
#include "parser.h"
#include <stdlib.h>

t_ambient	*create_ambient(double ratio, t_color color)
{
	t_ambient	*ambient;

	ambient = malloc(sizeof(t_ambient));
	if (ambient == NULL)
		return (HANDLE_ERROR_NULL);
	ambient->ratio = ratio;
	ambient->color = color;
	return (ambient);
}

// check amount of tokens
int	create_a(t_data_rule rule, char **tokens, t_map *map)
{
	float	ratio;
	t_color	color;

	(void)rule;
	if (get_valid_float(tokens[1], &ratio) == NO)
		return (NO);
	if (ratio < 0 || ratio > 1)
		return (NO);
	if (parser_color(tokens[2], &color) == NO)
		return (NO);
	printf("2\n");
	map->ambient = create_ambient(ratio, color);
	printf("3\n");
	if (map->ambient == NULL)
		return (NO);
	return (OK);
}
