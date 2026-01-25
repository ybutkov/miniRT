/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   obj_core.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybutkov <ybutkov@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/06 14:44:57 by ybutkov           #+#    #+#             */
/*   Updated: 2026/01/07 15:11:52 by ybutkov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "constants.h"
#include "objects.h"
#include <stdlib.h>

t_obj	*create_obj(t_color color, double reflection, double brightness)
{
	t_obj	*obj;

	obj = malloc(sizeof(t_obj));
	if (obj == NULL)
		return (HANDLE_ERROR_NULL);
	obj->brightness = brightness;
	obj->color = color;
	obj->reflection = reflection;
	obj->texture = NULL;
	obj->texture_intensity = 0.0;
	obj->methods = NULL;
	obj->data = NULL;
	obj->next = NULL;
	return (obj);
}
