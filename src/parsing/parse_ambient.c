/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_ambient.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skomyshe <skomyshe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/04 17:27:23 by skomyshe          #+#    #+#             */
/*   Updated: 2026/01/04 18:57:55 by skomyshe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

// Ambient A

int	is_valid_color_part(const char *s)
{
    int i;
    int n;

    i = 0;
    n = 0;
    if (!s || s[0] == '\0')
        return (NO);
    while (s[i])
    {
        if (s[i] < '0' || s[i] > '9')
            return (NO);
        n = n * 10 + (s[i] - '0');
        if (n > 255)
            return (NO);
        i++;
    }
    return (OK);
}

// Parse a string like "255,0,0" into t_color
int	is_valid_color(char	**split)
{
	if (!split || ft_split_len(split) != 3)
		return (NO);
	if (is_valid_color_part(split[0]) && is_valid_color_part(split[1])
		&& is_valid_color_part(split[2]))
		return (OK);
	return (NO);
}

int	is_valid_ambient(char **tokens)
{
	char	**split;

	if (ft_split_len(tokens) != 3)
		return (NO);
	if (is_validate_real(tokens[1]) == NO)
		return (NO);
	split = ft_split(tokens[2], ',');
	if (is_valid_color(split) == NO)
		return (free_split(split), NO);
	free_split(split);
	return (OK);
}

t_ambient	*parse_ambient(char **tokens)
{
	t_ambient	*result;

	if (is_valid_ambient(tokens) == NO)
		return (NULL);
	result = malloc(sizeof(t_ambient));
	if (result == NULL)
		return (NULL);
	result->ratio = ft_atof(tokens[1]);
	result->color = parse_color(tokens[2]);
	return (result);
}

// void	parse_ambient(char **tokens, t_scene *scene)
// {
// 	if (scene->ambient)
// 	exit_with_tokens(tokens, scene, "Ambient already defined");
// 	if (ft_split_len(tokens) != 3)
// 		error_exit("Invalid ambient format", NULL);
// 	scene->ambient = malloc(sizeof(t_ambient));
// 	scene->ambient->ratio = ft_atof(tokens[1]);
// 	scene->ambient->color = parse_color(tokens[2]);
// 	if (scene->ambient->ratio < 0.0 || scene->ambient->ratio > 1.0)
// 		error_exit("Ambient ratio out of range", NULL);
// }