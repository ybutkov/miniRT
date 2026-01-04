/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_camera.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skomyshe <skomyshe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/04 18:22:35 by skomyshe          #+#    #+#             */
/*   Updated: 2026/01/04 20:42:41 by skomyshe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

// camera C
int	is_validate_camera(char **tokens)
{
    char    **split;

    if (ft_split_len(tokens) != 4)
        return (NO);
    split = ft_split(tokens[2], ',');
    if (ft_split_len(split) != 3)
        return (free_split(split), NO);
    free_split(split);
    if (is_validate_real(tokens[3]) == NO)
        return (NO);
    return (OK);
}

t_camera	*parse_camera(char **tokens)
{
	t_camera	*result;

	if (is_validate_camera(tokens) == NO)
        return (NULL);
	result = malloc(sizeof(t_camera));
	if (result == NULL)
		return (NULL);
	result->pos = parse_vec3(tokens[1]);
	result->dir = parse_vec3(tokens[2]);
	result->fov = (int)ft_atof(tokens[3]);
	return (result);
}
