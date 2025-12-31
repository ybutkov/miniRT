/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions_wrapper_4.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybutkov <ybutkov@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/31 18:02:48 by ybutkov           #+#    #+#             */
/*   Updated: 2025/12/31 18:02:50 by ybutkov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"
#include "hooks.h"
#include <math.h>

void	key_p_action(t_app *app)
{
	app->map->projection = PROJ_PARALLEL;
}

void	key_i_action(t_app *app)
{
	app->map->projection = PROJ_ISO;
}

void	key_esc_action(t_app *app)
{
	close_window(app);
}
