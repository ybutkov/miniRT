/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_cylinder.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skomyshe <skomyshe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/04 19:28:49 by skomyshe          #+#    #+#             */
/*   Updated: 2026/01/07 23:33:16 by skomyshe         ###   ########.fr       */
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

t_object	*parse_cylinder(char **tokens)
{
	t_object	*result;
	t_vec3		direction;
	double		diameter;
	double		height;

	if (is_validate_cylinder(tokens) == NO)
		return (NULL);
	direction = parse_vec3(tokens[2]);
	if (is_normalized(direction) == NO)
		return (NULL);
	diameter = ft_atof(tokens[3]);
	height = ft_atof(tokens[4]);
	if (diameter <= 0 || height <= 0)
		return (NULL);
	result = malloc(sizeof(t_object));
	if (result == NULL)
		return (NULL);
	result->type = CYLINDER;
	result->pos = parse_vec3(tokens[1]);
	result->dir = direction;
	result->diameter = diameter;
	result->height = height;
	result->color = parse_color(tokens[5]);
	result->next = NULL;
	return (result);
}
