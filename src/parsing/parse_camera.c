/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_camera.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skomyshe <skomyshe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/04 18:22:35 by skomyshe          #+#    #+#             */
/*   Updated: 2026/01/04 19:06:13 by skomyshe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

// camera C
int	is_validate_camera(char **tokens)
{
    char    **split;

    if (ft_split_len(tokens) != 4)
        return (NO);
    split = ft_split(tokens[2], ',');
    if (ft_split_len(split) != 3)
        return (free_split(split), NO);
    free_split(split);
    if (is_validate_real(tokens[3]) == NO)
        return (NO);
    return (OK);
}

t_camera	*parse_camera(char **tokens)
{
	t_camera	*result;

	if (is_validate_camera(tokens) == NO)
        return (NULL);
	result = malloc(sizeof(t_camera));
	if (result == NULL)
		return (NULL);
	result->pos = parse_vec3(tokens[1]);
	result->dir = parse_vec3(tokens[2]);
	result->fov = (int)ft_atof(tokens[3]);
	return (result);
}

// void	parse_camera(char **tokens, t_scene *scene)
// {
// 	if (scene->ambient)
// 	exit_with_tokens(tokens, scene, "Camera already defined");
// 	if (ft_split_len(tokens) != 4)
// 		error_exit("Invalid camera format", NULL);
// 	scene->camera = malloc(sizeof(t_camera));
// 	scene->camera->pos = parse_vec3(tokens[1]);
// 	scene->camera->dir = parse_vec3(tokens[2]);
// 	scene->camera->fov = ft_atoi(tokens[3]);
// 	check_normalized(scene->camera->dir);
// 	if (scene->camera->fov < 0 || scene->camera->fov > 180)
// 		error_exit("Invalid FOV", NULL);
// }