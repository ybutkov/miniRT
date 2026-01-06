/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skomyshe <skomyshe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/04 01:53:26 by skomyshe          #+#    #+#             */
/*   Updated: 2026/01/06 22:42:22 by skomyshe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

#include "miniRT.h"

//ambient A
int	        is_valid_color(char	**split);
int	        is_valid_color_part(const char *s);
int	        is_valid_ambient(char **tokens);
t_ambient	*parse_ambient(char **tokens);

//camera C
int         is_validate_camera(char **tokens);
t_camera    *parse_camera(char **tokens);

// Light L
t_light		*parse_light(char **tokens);
int			is_validate_light(char **tokens);

// Sphere sp
t_object	*parse_sphere(char **tokens);
int			is_validate_sphere(char **tokens);

// Plane pl
t_object	*parse_plane(char **tokens);
int			is_validate_plane(char **tokens);

// Cylinder cy
t_object	*parse_cylinder(char **tokens);
int			is_validate_cylinder(char **tokens);

// Triangle tr
t_object    *parse_triangle(char **tokens);
int         is_validate_triangle(char **tokens);

int         is_normalized(t_vec3 v);

#endif