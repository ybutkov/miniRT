/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skomyshe <skomyshe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/31 21:34:14 by skomyshe          #+#    #+#             */
/*   Updated: 2026/01/06 22:41:30 by skomyshe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include "miniRT.h"
#include <fcntl.h>
#include "parser.h"
#include <unistd.h>
#include <string.h>

void	exit_with_tokens(char **tokens, t_scene *scene, const char *msg)
{
	if (tokens)
		free_split(tokens);
	error_exit(msg, scene);
}

void	parse_error_exit(t_parse_error err, int line_num, char *line)
{
	if (err == PARSE_UNKNOWN_ID)
	{
		ft_putstr_fd("Error\nUnknown identifier at line ", 2);
		ft_putnbr_fd(line_num, 2);
		ft_putstr_fd(": ", 2);
		ft_putendl_fd(line, 2);
	}
	else if (err == PARSE_MALLOC_FAIL)
		ft_putendl_fd("Error\nMemory allocation failed", 2);
	else if (err == PARSE_INVALID_FORMAT)
	{
		ft_putstr_fd("Error\nInvalid format at line ", 2);
		ft_putnbr_fd(line_num, 2);
		ft_putchar_fd('\n', 2);
	}
	exit(EXIT_FAILURE);
}

void	parse_file(int fd, t_scene *scene)
{
	char			*line;
	int				line_num;
	t_parse_error	err;

	line_num = 0;
	while ((line = get_next_line(fd)))
	{
		line_num++;
		err = parse_line(line, scene);
        printf("%d\n", err);
		if (!(err == PARSE_OK || err == PARSE_EMPTY_LINE))
        {
            free(line);
            close (fd);
			parse_error_exit(err, line_num, line);
        }
		free(line);
	}
}

t_parse_error	parse_line(char *line, t_scene *scene)
{
    char    **tokens;
    t_ambient   *ambient;
    t_camera    *camera;
    t_light     *light;
    t_object    *obj;

    if (line)
    {
        size_t len = strlen(line);
        if (len > 0 && line[len - 1] == '\n')
            line[len - 1] = '\0';
    }
    tokens = ft_split(line, ' ');
    if (!tokens)
        return (PARSE_MALLOC_FAIL);
    if (!tokens[0])
        return (free_split(tokens), PARSE_EMPTY_LINE);
    if (!ft_strncmp(tokens[0], "A", 2))
    {
        ambient = parse_ambient(tokens);
        if (ambient == NULL)
            return (free_split(tokens), PARSE_INVALID_FORMAT);
        scene->ambient = ambient;
    }
    else if (!ft_strncmp(tokens[0], "C", 2))
    {
        camera = parse_camera(tokens);
        if (camera == NULL)
            return (free_split(tokens), PARSE_INVALID_FORMAT);
        scene->camera = camera;
    }
    else if (!ft_strncmp(tokens[0], "L", 2))
    {
        light = parse_light(tokens);
        if (light == NULL)
            return (free_split(tokens), PARSE_INVALID_FORMAT);
        scene->light = light;
    }
    else if (!ft_strncmp(tokens[0], "sp", 3))
    {
        obj = parse_sphere(tokens);
        if (obj == NULL)
            return (free_split(tokens), PARSE_INVALID_FORMAT);
        obj->next = scene->objects;
        scene->objects = obj;
    }
    else if (!ft_strncmp(tokens[0], "pl", 3))
    {
        obj = parse_plane(tokens);
        if (obj == NULL)
            return (free_split(tokens), PARSE_INVALID_FORMAT);
        obj->next = scene->objects;
        scene->objects = obj;
    }
    else if (!ft_strncmp(tokens[0], "cy", 3))
    {
        obj = parse_cylinder(tokens);
        if (obj == NULL)
            return (free_split(tokens), PARSE_INVALID_FORMAT);
        obj->next = scene->objects;
        scene->objects = obj;
    }
    else if (!ft_strncmp(tokens[0], "tr", 3))
    {
        obj = parse_triangle(tokens);
        if (obj == NULL)
            return (free_split(tokens), PARSE_INVALID_FORMAT);
        obj->next = scene->objects;
        scene->objects = obj;
    }
    else
    {
        free_split(tokens);
        return (PARSE_UNKNOWN_ID);
    }
    free_split(tokens);
    return (PARSE_OK);
}

void	parse_scene(const char *filename, t_scene *scene)
{
	int		fd;

    fd = open(filename, O_RDONLY);
    if (fd < 0)
        error_exit("Failed to open file", NULL);
    parse_file(fd, scene);
    close(fd);
}
