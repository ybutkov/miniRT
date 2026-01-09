/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_camera.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybutkov <ybutkov@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/04 18:22:35 by skomyshe          #+#    #+#             */
/*   Updated: 2026/01/08 20:07:49 by ybutkov          ###   ########.fr       */
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

t_camera	*parse_camera(char **tokens)
{
	t_camera	*result;
	double		len;

	if (is_validate_camera(tokens) == NO)
		return (NULL);
	result = malloc(sizeof(t_camera));
	if (result == NULL)
		return (NULL);
	result->pos = parse_vec3(tokens[1]);
	result->dir = parse_vec3(tokens[2]);
	{
		len = sqrt(result->dir.x * result->dir.x + result->dir.y * result->dir.y
				+ result->dir.z * result->dir.z);
		if (len == 0.0)
		{
			free(result);
			return (NULL);
		}
		result->dir.x /= len;
		result->dir.y /= len;
		result->dir.z /= len;
	}
	result->fov = (int)ft_atof(tokens[3]);
	if (result->fov <= 0 || result->fov >= 180)
	{
		free(result);
		return (NULL);
	}
	return (result);
}
