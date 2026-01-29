/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions_wrapper_2.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybutkov <ybutkov@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/31 18:02:33 by ybutkov           #+#    #+#             */
/*   Updated: 2026/01/29 01:32:12 by ybutkov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "constants.h"
#include "hooks.h"
#include "miniRT.h"

void	key_minus_action(t_app *app)
{
	app->map->zoom_in(app->map, -app->map->zoom_size);
}

void	key_w_action(t_app *app)
{
	app->map->get_camera(app->map)->pos
		= vector_add(app->map->get_camera(app->map)->pos,
			vector_mult(app->map->get_camera(app->map)->dir, MOVE_CAMERA_STEP));
	update_camera(app->map->get_camera(app->map));
}

void	key_s_action(t_app *app)
{
	app->map->get_camera(app->map)->pos
		= vector_sub(app->map->get_camera(app->map)->pos,
			vector_mult(app->map->get_camera(app->map)->dir, MOVE_CAMERA_STEP));
	update_camera(app->map->get_camera(app->map));
}

void	key_a_action(t_app *app)
{
	app->map->get_camera(app->map)->pos
		= vector_sub(app->map->get_camera(app->map)->pos,
			vector_mult(app->map->get_camera(app->map)->right,
				MOVE_CAMERA_STEP));
	update_camera(app->map->get_camera(app->map));
}

void	key_d_action(t_app *app)
{
	app->map->get_camera(app->map)->pos
		= vector_add(app->map->get_camera(app->map)->pos,
			vector_mult(app->map->get_camera(app->map)->right,
				MOVE_CAMERA_STEP));
	update_camera(app->map->get_camera(app->map));
}
