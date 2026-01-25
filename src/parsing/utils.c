/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skomyshe <skomyshe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/01 19:01:39 by skomyshe          #+#    #+#             */
/*   Updated: 2026/01/25 21:05:46 by skomyshe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"
#include <stddef.h>
#include <stdlib.h>
#include <string.h>

int	get_valid_color_part(const char *s)
{
	int	i;
	int	n;

	if (!s || s[0] == '\0')
		return (-1);
	i = 0;
	n = 0;
	while (s[i])
	{
		if (s[i] < '0' || s[i] > '9')
			return (-1);
		n = n * 10 + (s[i] - '0');
		if (n > 255)
			return (-1);
		i++;
	}
	return (n);
}

void	error_exit(const char *msg, t_map *map)
{
	if (map)
		map->free(map);
	write(2, "Error\n", 6);
	write(2, msg, ft_strlen(msg));
	write(2, "\n", 1);
	exit(1);
}

void	free_split(char **split)
{
	int	i;

	i = 0;
	if (!split)
		return ;
	while (split[i])
	{
		free(split[i]);
		i++;
	}
	free(split);
}

int	ft_split_len(char **split)
{
	int	i;

	i = 0;
	if (!split)
		return (0);
	while (split[i])
		i++;
	return (i);
}
