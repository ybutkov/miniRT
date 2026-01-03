/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   colors.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybutkov <ybutkov@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/31 16:34:08 by ybutkov           #+#    #+#             */
/*   Updated: 2026/01/03 19:25:39 by ybutkov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COLORS_H
# define COLORS_H

# define COLOR_DEFAULT "0xFFFFFF"
# define COLOR_WHITE 0xFFFFFF
# define COLOR_NEON_LIME 0x39FF14
# define COLOR_CYAN 0x00FFFF
# define COLOR_YELLOW 0xFFFF00
# define COLOR_DEEP_INDIGO 0x191940

typedef struct s_color
{
	double	r;
	double	g;
	double	b;
}			t_color;

t_color		create_color(int r, int g, int b);
t_color		color_add(t_color c1, t_color c2);
t_color		color_mix(t_color c1, t_color c2, double intensity);
t_color		color_mult(t_color c1, double scalar);
int			color_to_int(t_color color);

#endif
