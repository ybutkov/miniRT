/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_axes_line.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybutkov <ybutkov@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/21 20:03:43 by ybutkov           #+#    #+#             */
/*   Updated: 2026/01/21 20:27:14 by ybutkov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "draw_internal.h"
#include "miniRT.h"
#include "vectors.h"

static void	init_algo(t_line_draw *line, t_line_algo *algo)
{
	algo->x0 = line->x0;
	algo->y0 = line->y0;
	algo->dx = abs(line->x1 - line->x0);
	algo->dy = abs(line->y1 - line->y0);
	algo->sx = -1;
	if (line->x0 < line->x1)
		algo->sx = 1;
	algo->sy = -1;
	if (line->y0 < line->y1)
		algo->sy = 1;
	algo->err = algo->dx - algo->dy;
}

static void	bresenham_step(t_line_algo *algo, int *e2)
{
	*e2 = 2 * algo->err;
	if (*e2 > -algo->dy)
	{
		algo->err -= algo->dy;
		algo->x0 += algo->sx;
	}
	if (*e2 < algo->dx)
	{
		algo->err += algo->dx;
		algo->y0 += algo->sy;
	}
}

void	draw_line_internal(t_line_draw *line)
{
	t_line_algo	algo;
	int			e2;
	int			x1;
	int			y1;

	x1 = line->x1;
	y1 = line->y1;
	init_algo(line, &algo);
	while (1)
	{
		ft_mlx_pixel_put(line->img, algo.x0, algo.y0, line->color);
		if (algo.x0 == x1 && algo.y0 == y1)
			break ;
		bresenham_step(&algo, &e2);
	}
}
