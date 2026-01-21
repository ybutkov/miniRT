/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_plane.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybutkov <ybutkov@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/04 19:19:32 by skomyshe          #+#    #+#             */
/*   Updated: 2026/01/08 22:52:07 by ybutkov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"
#include "parser.h"
#include <math.h>

// Plane pl
int	is_validate_plane(char **tokens)
{
	char	**split;

	if (ft_split_len(tokens) != 4)
		return (NO);
	split = ft_split(tokens[1], ',');
	if (ft_split_len(split) != 3)
		return (free_split(split), NO);
	if (is_valid_vec3_split(split) == NO)
		return (free_split(split), NO);
	free_split(split);
	split = ft_split(tokens[2], ',');
	if (ft_split_len(split) != 3)
		return (free_split(split), NO);
	if (is_valid_vec3_split(split) == NO)
		return (free_split(split), NO);
	free_split(split);
	split = ft_split(tokens[3], ',');
	if (is_valid_color(split) == NO)
		return (free_split(split), NO);
	free_split(split);
	return (OK);
}

t_obj	*parse_plane(char **tokens)
{
	t_obj	*result;
	t_vec3	direction;
	t_vec3	pos;
	t_color	color;

	if (is_validate_plane(tokens) == NO)
		return (NULL);
	direction = parse_vec3(tokens[2]);
	if (is_normalized(direction) == NO)
		return (NULL);
	pos = parse_vec3(tokens[1]);
	color = parse_color(tokens[3]);
	result = create_plane(pos, direction, color, REFLECTION_DEFAULT);
	if (result == NULL)
		return (HANDLE_ERROR_NULL);
	return (result);
}
