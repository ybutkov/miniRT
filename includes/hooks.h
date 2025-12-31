/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybutkov <ybutkov@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/31 16:35:50 by ybutkov           #+#    #+#             */
/*   Updated: 2025/12/31 16:36:12 by ybutkov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HOOKS_H
# define HOOKS_H

# include "miniRT.h"

# define AMOUNT_OF_KEY_ACTIONS 18

typedef struct s_app	t_app;

typedef void			(*t_key_action_fn)(t_app *app);

typedef struct s_key_action
{
	int					key;
	t_key_action_fn		action;
}						t_key_action;

typedef struct s_key_actions
{
	t_key_action		*actions;
	int					count;
	void				(*free)(struct s_key_actions *key_actions);
	t_key_action		*(*get_action)(struct s_key_actions *key_actions,
			int key);
}						t_key_actions;

#endif
