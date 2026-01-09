/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_light.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybutkov <ybutkov@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/04 19:03:20 by skomyshe          #+#    #+#             */
/*   Updated: 2026/01/08 22:56:11 by ybutkov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

// Light L
int	is_validate_light(char **tokens)
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
	if (is_validate_real(tokens[2]) == NO)
		return (NO);
	split = ft_split(tokens[3], ',');
	if (is_valid_color(split) == NO)
		return (free_split(split), NO);
	free_split(split);
	return (OK);
}

t_light	*parse_light(char **tokens)
{
	t_light	*result;
	t_vec3	pos;
	double	ratio;
	t_color	color;

	if (is_validate_light(tokens) == NO)
		return (HANDLE_ERROR_NULL);
	pos = parse_vec3(tokens[1]);
	ratio = ft_atof(tokens[2]);
	color = parse_color(tokens[3]);
	result = create_light(pos, ratio, color);
	if (result == NULL)
		return (HANDLE_ERROR_NULL);
	if (result->ratio < 0.0 || result->ratio > 1.0)
	{
		free(result);
		return (HANDLE_ERROR_NULL);
	}
	return (result);
}
