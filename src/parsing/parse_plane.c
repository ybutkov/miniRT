/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_plane.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skomyshe <skomyshe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/04 19:19:32 by skomyshe          #+#    #+#             */
/*   Updated: 2026/01/04 19:27:55 by skomyshe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* ************************************************************************** */

#include "parser.h"
#include <math.h>

// Plane pl
int	is_validate_plane(char **tokens)
{
    char	**split;

    if (ft_split_len(tokens) != 4)
        return (NO);
    split = ft_split(tokens[1], ',');
    if (ft_split_len(split) != 3)
        return (free_split(split), NO);
    free_split(split);
    split = ft_split(tokens[2], ',');
    if (ft_split_len(split) != 3)
        return (free_split(split), NO);
    free_split(split);
    split = ft_split(tokens[3], ',');
    if (is_valid_color(split) == NO)
        return (free_split(split), NO);
    free_split(split);
    return (OK);
}
static int	is_normalized(t_vec3 v)
{
    double	len;

    len = sqrt(v.x * v.x + v.y * v.y + v.z * v.z);
    if (fabs(len - 1.0) > 0.001)
        return (NO);
    return (OK);
}

t_object	*parse_plane(char **tokens)
{
    t_object	*result;
    t_vec3		direction;

    if (is_validate_plane(tokens) == NO)
        return (NULL);
    direction = parse_vec3(tokens[2]);
    if (is_normalized(direction) == NO)
        return (NULL);
    result = malloc(sizeof(t_object));
    if (result == NULL)
        return (NULL);
    result->type = PLANE;
    result->pos = parse_vec3(tokens[1]);
    result->dir = direction;
    result->color = parse_color(tokens[3]);
    result->next = NULL;
    return (result);
}