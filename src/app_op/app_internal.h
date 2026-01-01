/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   app_internal.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybutkov <ybutkov@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/01 21:25:15 by ybutkov           #+#    #+#             */
/*   Updated: 2026/01/01 21:26:09 by ybutkov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef APP_INTERNAL_H
# define APP_INTERNAL_H

# include "miniRT.h"

# ifdef __linux__
#  define IS_MAC 0
# else
#  define IS_MAC 1
# endif

void	draw_map(t_app *app);
void	ft_mlx_destroy_display(void *mlx);

#endif
