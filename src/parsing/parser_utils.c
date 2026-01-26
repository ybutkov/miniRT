/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skomyshe <skomyshe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/01 17:49:34 by skomyshe          #+#    #+#             */
/*   Updated: 2026/01/26 20:28:25 by skomyshe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "constants.h"
#include "miniRT.h"
#include "parser.h"
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int	get_valid_float(const char *str, float *res)
{
	if (!str)
		return (NO);
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
	if (get_valid_float(split[0], &xyz[0]) == NO || get_valid_float(split[1],
			&xyz[1]) == NO || get_valid_float(split[2], &xyz[2]) == NO)
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
