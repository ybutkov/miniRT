/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybutkov <ybutkov@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/04 01:53:26 by skomyshe          #+#    #+#             */
/*   Updated: 2026/01/22 23:19:17 by ybutkov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

# include "constants.h"
# include "miniRT.h"

# define MAX_AMOUNT_DATA_TYPE 10
# define AMOUNT_DATA_TYPE 10

typedef enum e_data_type
{
	VEC3,
	COLOR,
	FLOAT,
	INT
}				t_data_type;

typedef struct s_data_rule
{
	char		*data_type;
	t_data_type	params[MAX_AMOUNT_DATA_TYPE];
	int			min_params;
	int			max_params;
}				t_data_rule;

// ambient A
int				is_valid_color(char **split);
int				is_valid_color_part(const char *s);
int				is_valid_ambient(char **tokens);
t_ambient		*parse_ambient(char **tokens);

// camera C
int				is_validate_camera(char **tokens);
t_camera		*parse_camera(char **tokens, t_map *map);

// Light L
t_light			*parse_light(char **tokens);
int				is_validate_light(char **tokens);

// Sphere sp
t_obj			*parse_sphere(char **tokens);
int				is_validate_sphere(char **tokens);

// Plane pl
t_obj			*parse_plane(char **tokens);
int				is_validate_plane(char **tokens);

// Cylinder cy
t_obj			*parse_cylinder(char **tokens);
int				is_validate_cylinder(char **tokens);

// Triangle tr
t_obj			*parse_triangle(char **tokens);
int				is_validate_triangle(char **tokens);

int				is_normalized(t_vec3 v);
int				is_valid_vec3_split(char **split);

// new parsing
t_data_rule		get_data_rule(char *obj_type);
int				parser_color(char *str, t_color *c);
int				get_valid_color_part(const char *s);
int				parser_vec3(char *str, t_vec3 *vector);

#endif