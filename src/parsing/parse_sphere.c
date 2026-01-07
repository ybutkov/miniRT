/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_sphere.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skomyshe <skomyshe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/04 19:13:37 by skomyshe          #+#    #+#             */
/*   Updated: 2026/01/05 21:48:52 by skomyshe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

// Sphere sp
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

t_object	*parse_sphere(char **tokens)
{
    t_object	*result;

    if (is_validate_sphere(tokens) == NO)
        return (NULL);
    result = malloc(sizeof(t_object));
    if (result == NULL)
        return (NULL);
    result->type = SPHERE;
    result->pos = parse_vec3(tokens[1]);
    result->diameter = ft_atof(tokens[2]);
    result->color = parse_color(tokens[3]);
    if (result->diameter <= 0)
    {
        free(result);
        return (NULL);
    }
    result->next = NULL;
    return (result);
}
