/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skomyshe <skomyshe@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/01 17:49:34 by skomyshe          #+#    #+#             */
/*   Updated: 2026/01/01 20:26:44 by skomyshe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"
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
		error_exit("Invalid vector format");
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
	if (!split || ft_split_len(split) != 3)
		error_exit("Invalid color format");
	c.r = ft_atoi(split[0]);
	c.g = ft_atoi(split[1]);
	c.b = ft_atoi(split[2]);
	if (c.r < 0 || c.r > 255 || c.g < 0 || c.g > 255 || c.b < 0 || c.b > 255)
		error_exit("Color out of range");
	free_split(split);
	return (c);
}

// Check if a vector is normalized (length ~ 1)
void	check_normalized(t_vec3 v)
{
	double	len;

	len = sqrt(v.x * v.x + v.y * v.y + v.z * v.z);
	if (fabs(len - 1.0) > 0.001)
		error_exit("Vector not normalized");
}
