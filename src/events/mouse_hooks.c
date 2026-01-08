/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouse_hooks.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybutkov <ybutkov@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/31 18:03:19 by ybutkov           #+#    #+#             */
/*   Updated: 2026/01/08 19:24:22 by ybutkov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"
#include "mouse.h"
#include <math.h>

int	ft_mouse_press(int button, int x, int y, t_app *app)
{
	app->mouse.x = x;
	app->mouse.y = y;
	app->mouse.click_x = x;
	app->mouse.click_y = y;
	
	if (button == MOUSE_LEFT_BUTTON)
	{
		// Try to select an object at this position
		app->selected_obj = select_object_at_screen_pos(app, x, y);
		app->mouse.left_button = 1;
	}
	else if (button == MOUSE_RIGHT_BUTTON)
		app->mouse.right_button = 1;
	else if (button == MOUSE_MIDDLE_BUTTON)
		app->mouse.middle_button = 1;
	else if (button == MOUSE_SCROLL_UP)
		app->map->zoom_in(app->map, app->map->zoom_size);
	else if (button == MOUSE_SCROLL_DOWN)
		app->map->zoom_in(app->map, -app->map->zoom_size);
	app->map->is_change = 1;
	return (0);
}

int	ft_mouse_release(int button, int x, int y, t_app *app)
{
	(void)x;
	(void)y;
	if (button == MOUSE_LEFT_BUTTON)
	{
		app->mouse.left_button = 0;
		app->selected_obj = NULL;
	}
	else if (button == MOUSE_RIGHT_BUTTON)
		app->mouse.right_button = 0;
	else if (button == MOUSE_MIDDLE_BUTTON)
		app->mouse.middle_button = 0;
	return (0);
}

int	ft_mouse_move(int x, int y, t_app *app)
{
	t_mouse_state	*mouse;
	int				delta_x;
	int				delta_y;

	mouse = &app->mouse;
	if (mouse->prev_x == -1 && mouse->prev_y == -1)
	{
		mouse->prev_x = x;
		mouse->prev_y = y;
		return (0);
	}
	delta_x = x - mouse->prev_x;
	delta_y = y - mouse->prev_y;
	mouse->prev_x = x;
	mouse->prev_y = y;
	if (mouse->left_button && app->selected_obj)
	{
		move_selected_object(app, delta_x, delta_y);
	}
	else if (mouse->left_button)
		app->map->shift(app->map, delta_x, delta_y);
	else if (mouse->middle_button)
		app->map->rotate(app->map, copysign(0.01, delta_x), 0, 0);
	else if (mouse->right_button)
		app->map->rotate(app->map, 0, copysign(0.01, delta_y), 0);
	else
		return (0);
	app->map->is_change = 1;
	return (0);
}
