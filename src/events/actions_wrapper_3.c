/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions_wrapper_3.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybutkov <ybutkov@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/31 18:02:38 by ybutkov           #+#    #+#             */
/*   Updated: 2026/01/10 21:52:43 by ybutkov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"
#include "hooks.h"
#include "constants.h"

void	key_z_action(t_app *app)
{
	app->map->rotate(app->map, 0, 0, 0.05);
}

void	key_x_action(t_app *app)
{
	app->map->rotate(app->map, 0, 0, -0.05);
}

void	key_q_action(t_app *app)
{
	app->map->camera->pos = vector_add(app->map->camera->pos,
			vector_mult(app->map->camera->up, MOVE_CAMERA_STEP));
	update_camera(app->map->camera);
}

void	key_e_action(t_app *app)
{
	app->map->camera->pos = vector_add(app->map->camera->pos,
			vector_mult(app->map->camera->up, -MOVE_CAMERA_STEP));
	update_camera(app->map->camera);
}

void	key_r_action(t_app *app)
{
	app->map->reset(app->map);
}
