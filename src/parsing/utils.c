/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skomyshe <skomyshe@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/01 19:01:39 by skomyshe          #+#    #+#             */
/*   Updated: 2026/01/01 22:02:36 by skomyshe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void	error_exit(char *msg)
{
	if (msg)
		fprintf(stderr, "Error\n%s\n", msg);
	exit(EXIT_FAILURE);
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

double	ft_atof(const char *str)
{
	return (atof(str));
}
