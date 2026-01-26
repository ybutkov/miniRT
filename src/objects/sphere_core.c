/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sphere_core.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybutkov <ybutkov@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/04 17:49:55 by ybutkov           #+#    #+#             */
/*   Updated: 2026/01/26 17:10:20 by ybutkov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "constants.h"
#include "obj_internal.h"
#include "parser.h"
#include "vectors.h"
#include <stdlib.h>

double	sphere_intersect(t_obj *this, t_vec3 origin, t_vec3 dir)
{
	t_sphere	*sphere;
	t_vec3		oc;
	t_vec3		abc;
	double		t[2];

	sphere = (t_sphere *)this->data;
	oc = vector_sub(origin, sphere->center);
	abc.x = vector_dot_product(dir, dir);
	abc.y = 2.0 * vector_dot_product(oc, dir);
	abc.z = vector_dot_product(oc, oc) - sphere->radius_sq;
	if (solve_quadratic(abc, &t[0], &t[1]) == NO)
		return (-1.0);
	if (t[0] > EPSILON)
		return (t[0]);
	if (t[1] > EPSILON)
		return (t[1]);
	return (-1.0);
}

t_aabb	sphere_get_aabb(t_obj *this)
{
	t_aabb		aabb;
	t_sphere	*sphere;

	sphere = (t_sphere *)this->data;
	aabb.min = vector_sub_scalar(sphere->center, sphere->radius);
	aabb.max = vector_add_scalar(sphere->center, sphere->radius);
	return (aabb);
}

static t_obj	*create_sphere(t_vec3 pos, double diametr,
		t_color_reflect color_reflection)
{
	t_obj		*obj;
	t_sphere	*sphere;

	obj = create_obj(color_reflection.color, color_reflection.reflection,
			DEFAULT_BRIGHTNESS);
	if (obj == NULL)
		return (HANDLE_ERROR_NULL);
	sphere = malloc(sizeof(t_sphere));
	if (sphere == NULL)
		return (free(obj), HANDLE_ERROR_NULL);
	obj->methods = get_sphere_methods();
	sphere->center = pos;
	sphere->radius = diametr / 2.0;
	sphere->radius_sq = diametr * diametr / 4.0;
	obj->data = sphere;
	return (obj);
}

t_color	sphere_get_color(t_obj *obj, t_vec3 hit_point)
{
	t_texture		*tex;
	t_chess_texture	*chess;
	t_sphere		*sphere;
	double			u;
	double			v;
	t_color			tex_color;

	sphere = (t_sphere *)obj->data;
	get_sphere_uv(hit_point, sphere->center, &u, &v);
	if (!obj->texture || obj->texture_intensity <= 0.0)
		return (obj->color);
	if (obj->texture_type == TEXTURE_CHESS)
	{
		chess = (t_chess_texture *)obj->texture;
		return (get_chess_color(chess, u, v, obj->color));
	}
	tex = (t_texture *)obj->texture;
	tex_color = get_texture_color(tex, u, v);
	return (color_mix(obj->color, tex_color, obj->texture_intensity));
}

// check amount of tokens
int	create_sp(t_data_rule rule, char **tokens, t_map *map)
{
	t_vec3			pos;
	float			diametr;
	t_color_reflect	color_reflection;
	t_obj			*sphere;
	float			tex_intensity;
	t_chess_texture	*chess;

	(void)rule;
	if (parser_vec3(tokens[1], &pos) == NO
		|| get_valid_float(tokens[2], &diametr) == NO
		|| parser_color(tokens[3], &color_reflection.color) == NO)
		return (NO);
	if (get_valid_float(tokens[4], &color_reflection.reflection) != OK)
		color_reflection.reflection = DEFAULT_REFLECTION;
	sphere = create_sphere(pos, diametr, color_reflection);
	if (sphere == NULL)
		return (NO);
	if (tokens[5] && tokens[6] && tokens[7]
		&& ft_strcmp(tokens[5], "C") == 0)
	{
		chess = create_chess_texture(tokens[6], tokens[7]);
		if (chess)
		{
			sphere->texture = chess;
			sphere->texture_type = TEXTURE_CHESS;
			sphere->texture_intensity = 1.0;
		}
	}
	else if (tokens[5] && tokens[6] && get_valid_float(tokens[6],
			&tex_intensity) == OK)
	{
		sphere->texture = load_texture(map->mlx, tokens[5]);
		sphere->texture_type = TEXTURE_FILE;
		sphere->texture_intensity = tex_intensity;
	}
	map->add_obj(map, sphere);
	return (OK);
}
