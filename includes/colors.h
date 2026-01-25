/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   colors.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybutkov <ybutkov@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/31 16:34:08 by ybutkov           #+#    #+#             */
/*   Updated: 2026/01/25 20:15:05 by ybutkov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COLORS_H
# define COLORS_H

# include "rays.h"
# include "vectors.h"

# define COLOR_DEFAULT "0xFFFFFF"
# define COLOR_WHITE 0xFFFFFF
# define COLOR_NEON_LIME 0x39FF14
# define COLOR_CYAN 0x00FFFF
# define COLOR_YELLOW 0xFFFF00
# define COLOR_DEEP_INDIGO 0x191940

typedef t_vec3	t_color;

typedef struct s_color_reflect
{
	t_color	color;
	float	reflection;
}			t_color_reflect;

t_color			create_color(int r, int g, int b);
t_color			color_add(t_color c1, t_color c2);
t_color			color_mix(t_color c1, t_color c2, double intensity);
t_color			color_mult(t_color c1, double scalar);
t_color			color_product(t_color c1, t_color c2);
int				color_to_int(t_color color);
t_color			get_background_color(t_ray ray, struct s_map *map);

#endif
