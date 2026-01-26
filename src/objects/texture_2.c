/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture_2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybutkov <ybutkov@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/26 21:23:03 by ybutkov           #+#    #+#             */
/*   Updated: 2026/01/26 21:23:05 by ybutkov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "constants.h"
#include "objects.h"
#include "parser.h"
#include "mlx.h"
#include "libft.h"
#include <stdlib.h>
#include <math.h>

t_chess_texture	*create_chess_texture(char *color_str, char *scale_str)
{
	t_chess_texture	*chess;
	float			scale;

	if (!color_str || !scale_str)
		return (NULL);
	chess = malloc(sizeof(t_chess_texture));
	if (!chess)
		return (HANDLE_ERROR_NULL);
	if (parser_color(color_str, &chess->color2) == NO
		|| get_valid_float(scale_str, &scale) == NO)
	{
		free(chess);
		return (NULL);
	}
	chess->scale = (double)scale;
	return (chess);
}

t_color	default_get_color(t_obj *obj, t_vec3 hit_point)
{
	(void)hit_point;
	return (obj->color);
}
