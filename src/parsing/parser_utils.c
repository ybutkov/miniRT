/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybutkov <ybutkov@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/01 17:49:34 by skomyshe          #+#    #+#             */
/*   Updated: 2026/01/24 18:46:43 by ybutkov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "constants.h"
#include "miniRT.h"
#include "parser.h"
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Parse a string like "1.0,0.0,2.5" into t_vec3
t_vec3	parse_vec3(char *str)
{
	t_vec3	v;
	char	**split;

	split = ft_split(str, ',');
	if (!split || ft_split_len(split) != 3)
		error_exit("Invalid vector format", NULL);
	v.x = ft_atof(split[0]);
	v.y = ft_atof(split[1]);
	v.z = ft_atof(split[2]);
	free_split(split);
	return (v);
}
// ************************************************************************/
int	get_valid_float(const char *str, float *res)
{
	if (is_validate_real(str) == NO)
		return (NO);
	*res = ft_atof(str);
	return (OK);
}

int	parser_vec3(char *str, t_vec3 *vector)
{
	float	xyz[3];
	char	**split;

	split = ft_split(str, ',');
	if (!split || ft_split_len(split) != 3)
		return (free_split(split), NO);
	if (get_valid_float(split[0], &xyz[0]) == NO ||
		get_valid_float(split[1], &xyz[1]) == NO ||
		get_valid_float(split[2], &xyz[2]) == NO)
		return (free_split(split), NO);
	free_split(split);
	*vector = create_vector(xyz[0], xyz[1], xyz[2]);
	return (OK);
}

int	parser_color(char *str, t_color *color)
{
	char	**split;
	int		rgb[3];

	split = ft_split(str, ',');
	if (!split || ft_split_len(split) != 3)
		return (free_split(split), NO);
	rgb[0] = get_valid_color_part(split[0]);
	rgb[1] = get_valid_color_part(split[1]);
	rgb[2] = get_valid_color_part(split[2]);
	if (rgb[0] == -1 || rgb[1] == -1 || rgb[2] == -1)
		return (free_split(split), NO);
	*color = create_color(rgb[0], rgb[1], rgb[2]);
	free_split(split);
	return (1);
}
// ************************************************************************/
// Parse a string like "255,0,0" into t_color
t_color	parse_color(char *str)
{
	char	**split;
	t_color	c;

	split = ft_split(str, ',');
	c = create_color(ft_atoi(split[0]), ft_atoi(split[1]), ft_atoi(split[2]));
	free_split(split);
	return (c);
}

// Check if a vector is normalized (length ~ 1)
int	is_normalized(t_vec3 v)
{
	double	len;

	len = sqrt(v.x * v.x + v.y * v.y + v.z * v.z);
	if (fabs(len - 1.0) > 0.001)
		return (NO);
	return (OK);
}

/* each component must be a valid real number */
int	is_valid_vec3_split(char **split)
{
	if (!split)
		return (NO);
	if (ft_split_len(split) != 3)
		return (NO);
	if (is_validate_real(split[0]) == NO || is_validate_real(split[1]) == NO
		|| is_validate_real(split[2]) == NO)
		return (NO);
	return (OK);
}
