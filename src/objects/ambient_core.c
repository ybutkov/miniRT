/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ambient_core.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybutkov <ybutkov@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/05 20:10:10 by ybutkov           #+#    #+#             */
/*   Updated: 2026/01/08 21:41:07 by ybutkov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "objects.h"
#include "constants.h"
#include <stdlib.h>

t_ambient	*create_ambient(double ratio, t_color color)
{
	t_ambient	*ambient;

	ambient = malloc(sizeof(t_ambient));
	if (ambient == NULL)
		return (HANDLE_ERROR_NULL);
	ambient->ratio = ratio;
	ambient->color = color;
	return (ambient);
}
