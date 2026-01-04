/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   colors.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybutkov <ybutkov@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/31 16:34:08 by ybutkov           #+#    #+#             */
/*   Updated: 2026/01/04 21:33:08 by ybutkov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COLORS_H
# define COLORS_H

# include "vectors.h"
# include "rays.h"

# define COLOR_DEFAULT "0xFFFFFF"
# define COLOR_WHITE 0xFFFFFF
# define COLOR_NEON_LIME 0x39FF14
# define COLOR_CYAN 0x00FFFF
# define COLOR_YELLOW 0xFFFF00
# define COLOR_DEEP_INDIGO 0x191940

typedef t_vec3	t_color;

# define BG_COLOR_TOP create_vector(0.5, 0.7, 1.0)
# define BG_COLOR_BOTTOM create_vector(1.0, 1.0, 1.0)
# define BG_COLOR_BLACK create_vector(0.0, 0.0, 0.0)

// typedef struct s_color
// {
// 	double	r;
// 	double	g;
// 	double	b;
// }			t_color;

t_color			create_color(int r, int g, int b);
t_color			color_add(t_color c1, t_color c2);
t_color			color_mix(t_color c1, t_color c2, double intensity);
t_color			color_mult(t_color c1, double scalar);
int				color_to_int(t_color color);
t_color			get_background_color(t_ray ray);

#endif
