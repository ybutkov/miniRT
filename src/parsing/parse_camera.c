/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_camera.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybutkov <ybutkov@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/04 18:22:35 by skomyshe          #+#    #+#             */
/*   Updated: 2026/01/09 14:15:12 by ybutkov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

// camera C
int	is_validate_camera(char **tokens)
{
	char	**split;

	if (ft_split_len(tokens) != 4)
		return (NO);
	split = ft_split(tokens[2], ',');
	if (ft_split_len(split) != 3)
		return (free_split(split), NO);
	if (is_valid_vec3_split(split) == NO)
		return (free_split(split), NO);
	free_split(split);
	if (is_validate_real(tokens[3]) == NO)
		return (NO);
	return (OK);
}

t_camera	*parse_camera(char **tokens, t_map *map)
{
	t_camera	*result;
	t_vec3		pos;
	t_vec3		dir;
	double		fov;

	if (is_validate_camera(tokens) == NO)
		return (HANDLE_ERROR_NULL);
	pos = parse_vec3(tokens[1]);
	dir = parse_vec3(tokens[2]);
	fov = (int)ft_atof(tokens[3]);
	if (fov <= 0 || fov >= 180)
		return (HANDLE_ERROR_NULL);
	result = create_camera(pos, dir, fov, map);
	if (result == NULL)
		return (HANDLE_ERROR_NULL);
	return (result);
}
