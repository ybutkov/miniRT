/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_triangle.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybutkov <ybutkov@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/06 22:24:16 by skomyshe          #+#    #+#             */
/*   Updated: 2026/01/15 22:30:37 by ybutkov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

int	is_validate_triangle(char **tokens)
{
	char	**split;

	if (ft_split_len(tokens) != 5)
		return (NO);
	split = ft_split(tokens[1], ',');
	if (!split || ft_split_len(split) != 3)
		return (free_split(split), NO);
	if (is_valid_vec3_split(split) == NO)
		return (free_split(split), NO);
	free_split(split);
	split = ft_split(tokens[2], ',');
	if (!split || ft_split_len(split) != 3)
		return (free_split(split), NO);
	if (is_valid_vec3_split(split) == NO)
		return (free_split(split), NO);
	free_split(split);
	split = ft_split(tokens[3], ',');
	if (!split || ft_split_len(split) != 3)
		return (free_split(split), NO);
	if (is_valid_vec3_split(split) == NO)
		return (free_split(split), NO);
	free_split(split);
	split = ft_split(tokens[4], ',');
	if (!split || is_valid_color(split) == NO)
		return (free_split(split), NO);
	free_split(split);
	return (OK);
}

t_obj	*parse_triangle(char **tokens)
{
	t_obj			*result;
	t_vec3			p_1;
	t_vec3			p_2;
	t_vec3			p_3;
	t_color_reflect	color_reflection;

	if (is_validate_triangle(tokens) == NO)
		return (NULL);
	p_1 = parse_vec3(tokens[1]);
	p_2 = parse_vec3(tokens[2]);
	p_3 = parse_vec3(tokens[3]);
	color_reflection.color = parse_color(tokens[4]);
	color_reflection.reflection = REFLECTION_DEFAULT;
	result = create_triangle(p_1, p_2, p_3, color_reflection);
	return (result);
}
