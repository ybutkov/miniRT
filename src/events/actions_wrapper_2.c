/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions_wrapper_2.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybutkov <ybutkov@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/31 18:02:33 by ybutkov           #+#    #+#             */
/*   Updated: 2025/12/31 18:02:35 by ybutkov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"
#include "hooks.h"

void	key_minus_action(t_app *app)
{
	app->map->zoom_in(app->map, -app->map->zoom_size);
}

void	key_w_action(t_app *app)
{
	app->map->rotate(app->map, 0.05, 0, 0);
}

void	key_s_action(t_app *app)
{
	app->map->rotate(app->map, -0.05, 0, 0);
}

void	key_a_action(t_app *app)
{
	app->map->rotate(app->map, 0, 0.05, 0);
}

void	key_d_action(t_app *app)
{
	app->map->rotate(app->map, 0, -0.05, 0);
}
