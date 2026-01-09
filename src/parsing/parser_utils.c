/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybutkov <ybutkov@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/01 17:49:34 by skomyshe          #+#    #+#             */
/*   Updated: 2026/01/08 20:08:20 by ybutkov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"
#include "constants.h"
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

// Parse a string like "255,0,0" into t_color
t_color	parse_color(char *str)
{
	char	**split;
	t_color	c;

	split = ft_split(str, ',');
	c.r = ft_atoi(split[0]);
	c.g = ft_atoi(split[1]);
	c.b = ft_atoi(split[2]);
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
