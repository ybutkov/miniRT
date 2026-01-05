/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   light_core.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybutkov <ybutkov@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/05 18:39:54 by ybutkov           #+#    #+#             */
/*   Updated: 2026/01/05 18:47:04 by ybutkov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "objects.h"
#include "constants.h"
#include <stdlib.h>

t_light	*create_light(t_vec3 pos, double ratio, t_color color)
{
	t_light	*light;

	light = malloc(sizeof(t_light));
	if (light == NULL)
		return (HANDLE_ERROR_NULL);
	light->pos = pos;
	light->ratio = ratio;
	light->color = color;
	light->next = NULL;
	return (light);
}
