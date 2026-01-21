/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_types.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybutkov <ybutkov@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/15 15:52:26 by ybutkov           #+#    #+#             */
/*   Updated: 2026/01/15 21:52:51 by ybutkov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "obj_internal.h"

t_obj_type	box_get_type(void)
{
	return (BOX);
}

t_obj_type	cylinder_get_type(void)
{
	return (CYLINDER);
}

t_obj_type	plane_get_type(void)
{
	return (PLANE);
}

t_obj_type	sphere_get_type(void)
{
	return (SPHERE);
}

t_obj_type	triangle_get_type(void)
{
	return (TRIANGLE);
}
