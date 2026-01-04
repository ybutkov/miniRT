/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skomyshe <skomyshe@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/01 19:01:39 by skomyshe          #+#    #+#             */
/*   Updated: 2026/01/04 00:00:02 by skomyshe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stddef.h>

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

	if (!is_validate_real(str))
		error_exit("Invalid float value", NULL);
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


// void	parse_number(const char *str, t_atof *atof, int *i)
// {
// 	while (str[*i] >= '0' && str[*i] <= '9')
// 	{
// 		if (atof->dot_count == 0)
// 			atof->res = atof->res * 10.0f + (str[*i] - '0');
// 		else
// 		{
// 			atof->res = atof->res * 10.0f + (str[*i] - '0');
// 			atof->f *= 10.0f;
// 		}
// 		(*i)++;
// 	}
// 	if (str[*i] == '.')
// 	{
// 		atof->dot_count++;
// 		if (atof->dot_count > 1)
// 			ft_error();
// 		(*i)++;
// 		parse_number(str, atof, i);
// 	}
// }

// float	ft_atof(const char *str)
// {
// 	t_atof	atof;
// 	int		i;

// 	atof.res = 0.0f;
// 	atof.sign = 1.0f;
// 	atof.f = 1.0f;
// 	atof.dot_count = 0;
// 	i = 0;
// 	while (str[i] == ' ' || (str[i] >= 9 && str[i] <= 13))
// 		i++;
// 	if (str[i] == '-' || str[i] == '+')
// 	{
// 		if (str[i] == '-')
// 			atof.sign = -1.0f;
// 		i++;
// 	}
// 	if ((str[i] < '0' || str[i] > '9') && str[i] != '.')
// 		ft_error();
// 	parse_number(str, &atof, &i);
// 	if (str[i] != '\0')
// 		ft_error();
// 	return (atof.sign * (atof.res / atof.f));
// }
