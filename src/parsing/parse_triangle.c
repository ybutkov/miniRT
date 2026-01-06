/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_triangle.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skomyshe <skomyshe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/06 22:24:16 by skomyshe          #+#    #+#             */
/*   Updated: 2026/01/06 23:07:34 by skomyshe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

// Triangle tr
int	is_validate_triangle(char **tokens)
{
    char	**split;
    if (ft_split_len(tokens) != 5)
        return (NO);
    split = ft_split(tokens[1], ',');
    if (!split || ft_split_len(split) != 3)
        return (free_split(split), NO);
    free_split(split);
    split = ft_split(tokens[2], ',');
    if (!split || ft_split_len(split) != 3)
        return (free_split(split), NO);
    free_split(split);
    split = ft_split(tokens[3], ',');
    if (!split || ft_split_len(split) != 3)
        return (free_split(split), NO);
    free_split(split);
    split = ft_split(tokens[4], ',');
    if (!split || is_valid_color(split) == NO)
        return (free_split(split), NO);
    free_split(split);
    return (OK);
}

t_object    *parse_triangle(char **tokens)
{
    t_object	*result;

    if (is_validate_triangle(tokens) == NO)
        return (NULL);
    result = malloc(sizeof(t_object));
    if (result == NULL)
        return (NULL);
    result->type = TRIANGLE;
    result->pos = parse_vec3(tokens[1]);
    result->dir = parse_vec3(tokens[2]);
    result->diameter = 0.0;
    result->height = 0.0;
    result->color = parse_color(tokens[4]);
    result->next = NULL;
    return (result);
}