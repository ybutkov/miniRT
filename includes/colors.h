/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   colors.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybutkov <ybutkov@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/31 16:34:08 by ybutkov           #+#    #+#             */
/*   Updated: 2026/01/03 00:19:23 by ybutkov          ###   ########.fr       */
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

	int		(*rgb_to_int)(struct s_color *color);
	void	(*add)(struct s_color *this, struct s_color other);
	void	(*mix)(struct s_color *this, struct s_color color_obj,
			double intensity);
	void	(*mult)(struct s_color *this, double scalar);

}			t_color;

t_color		create_color(int r, int g, int b);

#endif
