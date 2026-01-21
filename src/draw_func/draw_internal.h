/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_internal.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybutkov <ybutkov@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/21 20:03:57 by ybutkov           #+#    #+#             */
/*   Updated: 2026/01/21 20:27:05 by ybutkov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DRAW_INTERNAL_H
# define DRAW_INTERNAL_H

# include "miniRT.h"

typedef struct s_line_draw
{
	t_img	*img;
	int		x0;
	int		y0;
	int		x1;
	int		y1;
	int		color;
}			t_line_draw;

typedef struct s_coord_info
{
	int		x;
	int		y;
	int		decimals;
}			t_coord_info;

typedef struct s_line_algo
{
	int		x0;
	int		y0;
	int		dx;
	int		dy;
	int		sx;
	int		sy;
	int		err;
}			t_line_algo;

#endif
