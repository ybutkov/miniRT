/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_cylinder.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybutkov <ybutkov@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/04 19:28:49 by skomyshe          #+#    #+#             */
/*   Updated: 2026/01/15 21:02:10 by ybutkov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include <math.h>

// Cylinder cy
int	is_validate_cylinder(char **tokens)
{
	char	**split;

	if (ft_split_len(tokens) != 6)
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
	if (is_validate_real(tokens[3]) == NO)
		return (NO);
	if (is_validate_real(tokens[4]) == NO)
		return (NO);
	split = ft_split(tokens[5], ',');
	if (is_valid_color(split) == NO)
		return (free_split(split), NO);
	free_split(split);
	return (OK);
}

t_obj	*parse_cylinder(char **tokens)
{
	t_obj	*result;
	t_vec3	direction;
	t_vec3	pos;
	double	diametr_height[2];
	t_color_reflect color_reflection;

	if (is_validate_cylinder(tokens) == NO)
		return (HANDLE_ERROR_NULL);
	direction = parse_vec3(tokens[2]);
	if (is_normalized(direction) == NO)
		return (HANDLE_ERROR_NULL);
	diametr_height[0] = ft_atof(tokens[3]);
	diametr_height[1] = ft_atof(tokens[4]);
	if (diametr_height[0] <= 0 || diametr_height[1] <= 0)
		return (HANDLE_ERROR_NULL);
	pos = parse_vec3(tokens[1]);
	color_reflection.color = parse_color(tokens[5]);
	color_reflection.reflection = REFLECTION_DEFAULT;
	result = create_cylinder(pos, direction, diametr_height, color_reflection);
	return (result);
}
