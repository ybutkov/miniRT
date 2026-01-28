/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybutkov <ybutkov@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/27 14:06:36 by ybutkov           #+#    #+#             */
/*   Updated: 2026/01/28 13:30:15 by ybutkov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "obj_internal.h"

t_aabb	get_empty_aabb(void)
{
	t_aabb	empty_aabb;

	ft_bzero(&empty_aabb, sizeof(t_aabb));
	empty_aabb.min = create_vector(0, 0, 0);
	empty_aabb.max = create_vector(0, 0, 0);
	return (empty_aabb);
}
