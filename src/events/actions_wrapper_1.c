/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions_wrapper_1.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybutkov <ybutkov@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/31 18:02:23 by ybutkov           #+#    #+#             */
/*   Updated: 2026/01/12 20:34:55 by ybutkov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"
#include "hooks.h"
#include "constants.h"

void	key_up_action(t_app *app)
{
	rotate_camera(app->map->camera, create_vector(1, 0, 0), ROTATE_CAMERA_STEP * DEGREE_TO_RAD);
	update_camera(app->map->camera);
}

void	key_down_action(t_app *app)
{
	rotate_camera(app->map->camera, create_vector(-1, 0, 0), ROTATE_CAMERA_STEP * DEGREE_TO_RAD);
	update_camera(app->map->camera);
}

void	 key_left_action(t_app *app)
{
	rotate_camera(app->map->camera, create_vector(0, 1, 0), ROTATE_CAMERA_STEP * DEGREE_TO_RAD);
	update_camera(app->map->camera);
}

void	key_right_action(t_app *app)
{
	rotate_camera(app->map->camera, create_vector(0, -1, 0), ROTATE_CAMERA_STEP * DEGREE_TO_RAD);
	update_camera(app->map->camera);
}

void	key_plus_action(t_app *app)
{
	app->map->zoom_in(app->map, app->map->zoom_size);
}
