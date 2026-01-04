/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera_core.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybutkov <ybutkov@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/04 00:04:02 by ybutkov           #+#    #+#             */
/*   Updated: 2026/01/04 16:55:36 by ybutkov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "objects.h"
#include "map.h"
#include <math.h>

t_camera	create_camera(t_vec3 pos, t_vec3 dir, double fov, t_map *map)
{
	t_camera cam;
	t_vec3 u, v, w;
	double h;

	cam.pos = pos;
	cam.fov = fov;
	cam.aspect_ratio = (double)map->width / (double)map->height;
	// 1. Рассчитываем размер экрана через FOV	
    // tan(fov/2) дает половину высоты экрана на расстоянии 1.0 от камеры
	h = tan((fov * M_PI / 180.0) / 2.0);
	double viewport_height = 2.0 * h;
	double viewport_width = cam.aspect_ratio * viewport_height;
	// 2. Строим базис камеры (направления право, верх, вперед)
	w = vector_norm(dir); // Вперед (Z-ось камеры)
	// Временный вектор "вверх" для расчета (мировая ось Y)
	t_vec3 v_up = create_vector(0, 1, 0);
		// Защита: если камера смотрит строго вверх/вниз, меняем  v_up
	if (fabs(w.y) > 0.99)
		v_up = create_vector(0, 0, 1);
	u = vector_norm(vector_cross(v_up, w)); // Вправо (X-ось камеры)
    v = vector_cross(w, u);	// Вверх (Y-ось камеры)
	// 3. Рассчитываем векторы плоскости экрана
	cam.horizontal = vector_mult(u, viewport_width);
	cam.vertical = vector_mult(v, viewport_height);
	// 4. Находим левый нижний угол (Lower Left Corner)
	// LLC = Origin + Forward - (Horizontal / 2) - (Vertical / 2)
	t_vec3 h_half = vector_mult(cam.horizontal, 0.5);
	t_vec3 v_half = vector_mult(cam.vertical, 0.5);
	cam.lower_left_pos = vector_add(cam.pos, w);
	cam.lower_left_pos = vector_sub(cam.lower_left_pos, h_half);
	cam.lower_left_pos = vector_sub(cam.lower_left_pos, v_half);
	return (cam);
}
