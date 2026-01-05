/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ambient_core.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybutkov <ybutkov@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/05 20:10:10 by ybutkov           #+#    #+#             */
/*   Updated: 2026/01/05 20:22:27 by ybutkov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "objects.h"

t_ambient	create_ambient(double ratio, t_color color)
{
	t_ambient	ambient;

	ambient.ratio = ratio;
	ambient.color = color;
	return (ambient);
}
