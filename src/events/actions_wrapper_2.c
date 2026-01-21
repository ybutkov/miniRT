/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions_wrapper_2.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybutkov <ybutkov@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/31 18:02:33 by ybutkov           #+#    #+#             */
/*   Updated: 2026/01/08 21:36:02 by ybutkov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"
#include "hooks.h"
#include "constants.h"

void	key_minus_action(t_app *app)
{
	app->map->zoom_in(app->map, -app->map->zoom_size);
}

void	key_w_action(t_app *app)
{
	app->map->camera->pos = vector_add(app->map->camera->pos,
			vector_mult(app->map->camera->dir, MOVE_CAMERA_STEP));
	update_camera(app->map->camera);
}

void	key_s_action(t_app *app)
{
	app->map->camera->pos = vector_sub(app->map->camera->pos,
			vector_mult(app->map->camera->dir, MOVE_CAMERA_STEP));
	update_camera(app->map->camera);
}

void	key_a_action(t_app *app)
{
	app->map->camera->pos = vector_sub(app->map->camera->pos,
			vector_mult(app->map->camera->right, MOVE_CAMERA_STEP));
	update_camera(app->map->camera);
}

void	key_d_action(t_app *app)
{
	app->map->camera->pos = vector_add(app->map->camera->pos,
			vector_mult(app->map->camera->right, MOVE_CAMERA_STEP));
	update_camera(app->map->camera);
}
