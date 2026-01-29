/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions_wrapper_3.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybutkov <ybutkov@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/31 18:02:38 by ybutkov           #+#    #+#             */
/*   Updated: 2026/01/29 03:10:21 by ybutkov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"
#include "hooks.h"
#include "constants.h"

void	key_z_action(t_app *app)
{
	app->map->get_camera(app->map)->pos
		= vector_add(app->map->get_camera(app->map)->pos,
			vector_mult(app->map->get_camera(app->map)->up, -MOVE_CAMERA_STEP));
	update_camera(app->map->get_camera(app->map));
}

void	key_q_action(t_app *app)
{
	app->map->get_camera(app->map)->pos
		= vector_add(app->map->get_camera(app->map)->pos,
			vector_mult(app->map->get_camera(app->map)->up, MOVE_CAMERA_STEP));
	update_camera(app->map->get_camera(app->map));
}

void	key_tab_action(t_app *app)
{
	(void)app;
	app->map->camera = app->map->get_camera(app->map)->next;
}
