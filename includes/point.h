/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   point.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybutkov <ybutkov@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/31 16:35:14 by ybutkov           #+#    #+#             */
/*   Updated: 2025/12/31 16:35:17 by ybutkov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef POINT_H
# define POINT_H

# include <stdint.h>

typedef int16_t		t_z_type;
typedef uint32_t	t_color_type;

typedef struct s_point_2d
{
	int				x;
	int				y;
	t_color_type	color;
}					t_point_2d;

typedef struct s_point_3d
{
	double			x;
	double			y;
	double			z;
}					t_point_3d;

typedef struct s_point
{
	t_z_type		z;
	t_color_type	color;
} __attribute__((packed))	t_point;

#endif
