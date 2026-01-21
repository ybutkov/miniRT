/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   point.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybutkov <ybutkov@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/31 16:35:14 by ybutkov           #+#    #+#             */
/*   Updated: 2026/01/18 00:11:29 by ybutkov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef POINT_H
# define POINT_H

# include <stdint.h>

typedef struct s_point_2d
{
	int		x;
	int		y;
}			t_point_2d;

typedef struct s_ratio
{
	double	x;
	double	y;
}			t_ratio;

#endif
