/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skomyshe <skomyshe@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/31 21:34:14 by skomyshe          #+#    #+#             */
/*   Updated: 2026/01/01 21:58:08 by skomyshe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include "miniRT.h"
#include <fcntl.h>
#include <unistd.h>

void	parse_line(char *line, t_scene *scene)
{
	char	**tokens;

	tokens = ft_split(line, ' ');
	if (!tokens || !tokens[0])
		return ;
	if (!ft_strncmp(tokens[0], "A", 2))
		parse_ambient(tokens, scene);
	else if (!ft_strncmp(tokens[0], "C", 2))
		parse_camera(tokens, scene);
	else if (!ft_strncmp(tokens[0], "L", 2))
		parse_light(tokens, scene);
	else if (!ft_strncmp(tokens[0], "sp", 3))
		parse_sphere(tokens, scene);
	else if (!ft_strncmp(tokens[0], "pl", 3))
		parse_plane(tokens, scene);
	else if (!ft_strncmp(tokens[0], "cy", 3))
		parse_cylinder(tokens, scene);
	else
		error_exit("Unknown identifier");
	free_split(tokens);
}

void	parse_scene(char *filename, t_scene *scene)
{
	int		fd;
	char	*line;

	fd = open(filename, O_RDONLY);
	if (fd < 0)
		error_exit("Failed to open file");
	while ((line = get_next_line(fd)))
	{
		parse_line(line, scene);
		free(line);
	}
	close(fd);
}
