/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color_core.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybutkov <ybutkov@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/02 23:20:16 by ybutkov           #+#    #+#             */
/*   Updated: 2026/01/03 00:18:29 by ybutkov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "colors.h"

static int	color_to_int(t_color *this)
{
	int	r;
	int	g;
	int	b;

	r = (int)(fmin(1.0, fmax(0.0, this->r)) * 255.999);
	g = (int)(fmin(1.0, fmax(0.0, this->g)) * 255.999);
	b = (int)(fmin(1.0, fmax(0.0, this->b)) * 255.999);
	return (r << 16 | g << 8 | b);
}

static void	color_mix(t_color *this, t_color light, double intensity)
{
	this->r = this->r * (light.r * intensity);
	this->g = this->g * (light.g * intensity);
	this->b = this->b * (light.b * intensity);
}

static void	color_mult(t_color *this, double scalar)
{
	this->r *= scalar;
	this->g *= scalar;
	this->b *= scalar;
}

static void	color_add(t_color *this, t_color other)
{
	this->r += other.r;
	this->g += other.g;
	this->b += other.b;
}

t_color	create_color(int r, int g, int b)
{
	t_color	color;

	color.r = (double)r / 255.0;
	color.g = (double)g / 255.0;
	color.b = (double)b / 255.0;
	color.rgb_to_int = color_to_int;
	color.mix = color_mix;
	color.add = color_add;
	color.mult = color_mult;
	return (color);
}
