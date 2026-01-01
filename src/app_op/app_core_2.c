/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   app_core_2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybutkov <ybutkov@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/01 21:24:49 by ybutkov           #+#    #+#             */
/*   Updated: 2026/01/01 21:24:52 by ybutkov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <mlx.h>

#ifdef __linux__

void	ft_mlx_destroy_display(void *mlx)
{
	mlx_destroy_display(mlx);
}

#else

void	ft_mlx_destroy_display(void *mlx)
{
	(void)mlx;
	return ;
}
#endif