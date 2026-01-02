/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skomyshe <skomyshe@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/02 19:37:14 by skomyshe          #+#    #+#             */
/*   Updated: 2026/01/02 19:47:42 by skomyshe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

// void	ft_error(t_scene *scene)
// {
// 	if (scene)
// 		free_scene(scene);
// 	write(2, "Error\n", 6);
// 	exit(EXIT_FAILURE);
// }
void	ft_error(void)
{
	write(2, "Error\n", 6);
	exit(EXIT_FAILURE);
}
