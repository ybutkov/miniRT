/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_ambient.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybutkov <ybutkov@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/04 17:27:23 by skomyshe          #+#    #+#             */
/*   Updated: 2026/01/08 20:07:34 by ybutkov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

// Ambient A
int	is_valid_color_part(const char *s)
{
	int	i;
	int	n;

	if (!s || s[0] == '\0')
		return (NO);
	i = 0;
	n = 0;
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

int	is_valid_color(char **split)
{
	if (!split || ft_split_len(split) != 3)
		return (NO);
	if (!is_valid_color_part(split[0]) || !is_valid_color_part(split[1])
		|| !is_valid_color_part(split[2]))
		return (NO);
	return (OK);
}

int	is_valid_ambient(char **tokens)
{
	char	**split;
	double	ratio;

	if (!tokens || ft_split_len(tokens) != 3)
		return (NO);
	if (is_validate_real(tokens[1]) == NO)
		return (NO);
	ratio = ft_atof(tokens[1]);
	if (ratio < 0.0 || ratio > 1.0)
		return (NO);
	split = ft_split(tokens[2], ',');
	if (!split)
		return (NO);
	if (is_valid_color(split) == NO)
	{
		free_split(split);
		return (NO);
	}
	free_split(split);
	return (OK);
}

t_ambient	*parse_ambient(char **tokens)
{
	t_ambient	*result;

	if (is_valid_ambient(tokens) == NO)
		return (NULL);
	result = malloc(sizeof(t_ambient));
	if (!result)
		return (NULL);
	result->ratio = ft_atof(tokens[1]);
	result->color = parse_color(tokens[2]);
	return (result);
}
