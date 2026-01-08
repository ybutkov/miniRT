/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouse.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybutkov <ybutkov@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/31 16:34:40 by ybutkov           #+#    #+#             */
/*   Updated: 2025/12/31 16:34:42 by ybutkov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MOUSE_H
# define MOUSE_H

# define MOUSE_LEFT_BUTTON 1
# define MOUSE_RIGHT_BUTTON 3
# define MOUSE_MIDDLE_BUTTON 2
# define MOUSE_SCROLL_UP 4
# define MOUSE_SCROLL_DOWN 5

typedef struct s_mouse_state
{
	int	left_button;
	int	right_button;
	int	middle_button;
	int	x;
	int	y;
	int	prev_x;
	int	prev_y;
	int	click_x;
	int	click_y;
}		t_mouse_state;

#endif
