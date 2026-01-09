/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rays.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybutkov <ybutkov@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/03 21:28:01 by ybutkov           #+#    #+#             */
/*   Updated: 2026/01/08 21:32:46 by ybutkov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RAYS_H
# define RAYS_H
# include "vectors.h"

typedef struct s_camera	t_camera;
typedef struct s_obj	t_obj;
typedef t_vec3			t_color;
typedef struct s_map	t_map;

typedef struct s_ray
{
	t_vec3				start;
	t_vec3				direction;
}						t_ray;

t_ray					create_ray(t_vec3 start, t_vec3 direction);
t_vec3					ray_at_pos(t_ray ray, double pos);
t_ray					get_ray(t_camera *cam, double x_ratio, double y_ratio);
t_color					trace_ray(t_ray ray, t_obj *obj, t_map *map, int depth);

#endif
