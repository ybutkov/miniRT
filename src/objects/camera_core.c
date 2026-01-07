/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera_core.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybutkov <ybutkov@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/04 00:04:02 by ybutkov           #+#    #+#             */
/*   Updated: 2026/01/05 17:46:54 by ybutkov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "objects.h"
#include "map.h"
#include <math.h>

// (dir, right, up) (w,u,v)
void	update_camera(t_camera	*cam)
{
	t_vec3	v_up;
	t_vec3	h_half;
	t_vec3	v_half;
	double	viewport_height;
	double	viewport_width;

	viewport_height = 2.0 * tan((cam->fov * M_PI / 180.0) / 2.0);
	viewport_width = cam->aspect_ratio * viewport_height;
	v_up = create_vector(0, 1, 0);
	if (fabs(cam->dir.y) > 0.99)
		v_up = create_vector(0, 0, 1);
	cam->right = vector_norm(vector_cross(cam->dir, v_up));
	cam->up = vector_cross(cam->right, cam->dir);
	cam->horizontal = vector_mult(cam->right, viewport_width);
	cam->vertical = vector_mult(cam->up, viewport_height);
	h_half = vector_mult(cam->horizontal, 0.5);
	v_half = vector_mult(cam->vertical, 0.5);
	cam->lower_left_pos = vector_add(cam->pos, cam->dir);
	cam->lower_left_pos = vector_sub(cam->lower_left_pos, h_half);
	cam->lower_left_pos = vector_sub(cam->lower_left_pos, v_half);
}

t_camera	create_camera(t_vec3 pos, t_vec3 dir, double fov, t_map *map)
{
	t_camera	cam;

	cam.pos = pos;
	cam.fov = fov;
	cam.dir = vector_norm(dir);
	cam.aspect_ratio = (double)map->width / (double)map->height;
	update_camera(&cam);
	return (cam);
}
