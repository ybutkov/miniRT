/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skomyshe <skomyshe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/25 20:56:41 by skomyshe          #+#    #+#             */
/*   Updated: 2026/01/25 21:01:47 by skomyshe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"
#include <stddef.h>
#include <stdlib.h>

static int	parse_number(const char *str, int *i)
{
	int	digit;

	digit = 0;
	while (str[*i] >= '0' && str[*i] <= '9')
	{
		digit = 1;
		(*i)++;
	}
	if (str[*i] == '.')
	{
		(*i)++;
		while (str[*i] >= '0' && str[*i] <= '9')
		{
			digit = 1;
			(*i)++;
		}
	}
	return (digit);
}

int	is_validate_real(const char *str)
{
	int	i;
	int	digit;

	i = 0;
	while (str[i] == ' ' || (str[i] >= 9 && str[i] <= 13))
		i++;
	if (str[i] == '+' || str[i] == '-')
		i++;
	digit = parse_number(str, &i);
	while (str[i] == ' ' || (str[i] >= 9 && str[i] <= 13))
		i++;
	if (str[i] != '\0')
		return (0);
	return (digit);
}

static float	parse_fraction(const char *str, int *i)
{
	float	res;
	float	div;

	res = 0.0f;
	div = 1.0f;
	if (str[*i] == '.')
	{
		(*i)++;
		while (str[*i] >= '0' && str[*i] <= '9')
		{
			res = res * 10.0f + (str[*i] - '0');
			div *= 10.0f;
			(*i)++;
		}
	}
	return (res / div);
}

float	ft_atof(const char *str)
{
	float	res;
	float	sign;
	int		i;

	res = 0.0f;
	sign = 1.0f;
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
	res += parse_fraction(str, &i);
	return (res * sign);
}
