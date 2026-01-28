/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sphere_core.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybutkov <ybutkov@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/04 17:49:55 by ybutkov           #+#    #+#             */
/*   Updated: 2026/01/28 20:18:33 by ybutkov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "constants.h"
#include "obj_internal.h"
#include "parser.h"
#include "vectors.h"
#include <stdlib.h>

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
	return (color_mix(obj->color, get_texture_color(tex, u, v),
			obj->texture_intensity));
}

static void	get_additional_props(char **tokens, t_obj *sphere, t_map *map)
{
	t_chess_texture	*chess;
	float			tex_intensity;

	if (!tokens[4])
		return ;
	if (tokens[5] && tokens[6] && tokens[7] && ft_strcmp(tokens[5], "C") == 0)
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
}

// check amount of tokens
int	create_sp(t_data_rule rule, char **tokens, t_map *map)
{
	t_vec3			pos;
	float			diametr;
	t_color_reflect	color_reflection;
	t_obj			*sphere;

	(void)rule;
	if (parser_vec3(tokens[1], &pos) == NO
		|| get_valid_float(tokens[2], &diametr) == NO
		|| parser_color(tokens[3], &color_reflection.color) == NO)
		return (NO);
	if (diametr <= 0)
		return (NO);
	if (get_valid_float(tokens[4], &color_reflection.reflection) != OK)
		color_reflection.reflection = DEFAULT_REFLECTION;
	if (color_reflection.reflection < 0 || color_reflection.reflection > 1)
		return (NO);
	sphere = create_sphere(pos, diametr, color_reflection);
	if (sphere == NULL)
		return (NO);
	get_additional_props(tokens, sphere, map);
	map->add_obj(map, sphere);
	return (OK);
}
