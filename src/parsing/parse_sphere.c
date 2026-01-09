/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_sphere.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybutkov <ybutkov@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/04 19:13:37 by skomyshe          #+#    #+#             */
/*   Updated: 2026/01/09 18:59:38 by ybutkov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "objects.h"
#include "parser.h"


int	is_validate_sphere(char **tokens)
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

t_obj	*parse_sphere(char **tokens)
{
	t_obj	*result;
	t_vec3	pos;
	double	diametr;
	t_color	color;

	if (is_validate_sphere(tokens) == NO)
		return (HANDLE_ERROR_NULL);
	pos = parse_vec3(tokens[1]);
	diametr = (double)ft_atof(tokens[2]);
	color = parse_color(tokens[3]);
	result = create_sphere(pos, diametr, color, REFLECTION_DEFAULT);
	if (diametr <= 0)
	{
		free(result);
		return (HANDLE_ERROR_NULL);
	}
	return (result);
}
