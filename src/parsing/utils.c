/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skomyshe <skomyshe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/01 19:01:39 by skomyshe          #+#    #+#             */
/*   Updated: 2026/01/08 18:23:22 by skomyshe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"
#include <stddef.h>
#include <stdlib.h>
#include <string.h>

void	error_exit(const char *msg, t_scene *scene)
{
	if (scene)
		free_scene(scene);
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

int	is_validate_real(const char *str)
{
	int	i;
	int	dot;
	int	digit;

	i = 0;
	dot = 0;
	digit = 0;
	(void)0;
	while (str[i] == ' ' || (str[i] >= 9 && str[i] <= 13))
		i++;
	if (str[i] == '+' || str[i] == '-')
		i++;
	while (str[i] >= '0' && str[i] <= '9')
	{
		digit = 1;
		i++;
	}
	if (str[i] == '.')
	{
		dot = 1;
		i++;
		while (str[i] >= '0' && str[i] <= '9')
		{
			digit = 1;
			i++;
		}
	}
	while (str[i] == ' ' || (str[i] >= 9 && str[i] <= 13))
		i++;
	if (str[i] != '\0')
		return (0);
	return (digit);
}

float	ft_atof(const char *str)
{
	float	res;
	float	sign;
	float	div;
	int		i;

	res = 0.0f;
	sign = 1.0f;
	div = 1.0f;
	i = 0;
	while (str[i] == ' ' || (str[i] >= 9 && str[i] <= 13))
		i++;
	if (str[i] == '+' || str[i] == '-')
	{
		if (str[i] == '-')
			sign = -1.0f;
		i++;
	}
	while (str[i] >= '0' && str[i] <= '9')
	{
		res = res * 10.0f + (str[i] - '0');
		i++;
	}
	if (str[i] == '.')
	{
		i++;
		while (str[i] >= '0' && str[i] <= '9')
		{
			res = res * 10.0f + (str[i] - '0');
			div *= 10.0f;
			i++;
		}
	}
	return (res * sign / div);
}
