/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rays.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybutkov <ybutkov@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/03 21:28:01 by ybutkov           #+#    #+#             */
/*   Updated: 2026/01/03 21:46:47 by ybutkov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RAYS_H
# define RAYS_H

# include "vectors.h"

typedef struct s_ray
{
	t_vec3	start;
	t_vec3	direction;
}			t_ray;

t_ray		create_ray(t_vec3 start, t_vec3 direction);
t_vec3		ray_at_pos(t_ray ray, double pos);

#endif
