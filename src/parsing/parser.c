/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skomyshe <skomyshe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/31 21:34:14 by skomyshe          #+#    #+#             */
/*   Updated: 2026/01/26 21:29:30 by skomyshe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include "miniRT.h"
#include "parser.h"
#include <fcntl.h>
#include <string.h>
#include <unistd.h>

static void	normalize_line(char *line)
{
	size_t	i;
	size_t	j;

	if (!line)
		return ;
	i = 0;
	while (line[i])
	{
		if (line[i] == '\t')
			line[i] = ' ';
		if (line[i] == ',')
		{
			j = i + 1;
			while (line[j] == ' ' || line[j] == '\t')
				++j;
			if (j > i + 1)
				memmove(&line[i + 1], &line[j], ft_strlen(&line[j]) + 1);
		}
		++i;
	}
}

static t_parse_error	process_tokens(char *line, t_map *map)
{
	char		**tokens;
	t_data_rule	data_rule;

	tokens = ft_split(line, ' ');
	if (!tokens)
		return (PARSE_MALLOC_FAIL);
	if (!tokens[0])
		return (free_split(tokens), PARSE_EMPTY_LINE);
	data_rule = get_data_rule(tokens[0]);
	if (data_rule.create(data_rule, tokens, map) == NO)
		return (free_split(tokens), PARSE_INVALID_FORMAT);
	free_split(tokens);
	return (PARSE_OK);
}

t_parse_error	parse_line_new(char *line, t_map *map)
{
	size_t	len;
	size_t	i;

	if (line)
	{
		len = ft_strlen(line);
		if (len > 0 && line[len - 1] == '\n')
			line[len - 1] = '\0';
		{
			i = 0;
			while (line[i])
			{
				if (line[i] == '\t')
					line[i] = ' ';
				++i;
			}
		}
	}
	normalize_line(line);
	return (process_tokens(line, map));
}

void	parse_file(int fd, t_map *map)
{
	char			*line;
	int				line_num;
	t_parse_error	err;

	line_num = 0;
	line = get_next_line(fd);
	while (line)
	{
		line_num++;
		err = parse_line_new(line, map);
		if (!(err == PARSE_OK || err == PARSE_EMPTY_LINE))
		{
			free(line);
			close(fd);
			parse_error_exit(err, line_num, line);
		}
		free(line);
		line = get_next_line(fd);
	}
}

void	parse_scene(const char *filename, t_map *map)
{
	int	fd;

	fd = open(filename, O_RDONLY);
	if (fd < 0)
		error_exit("Failed to open file", NULL);
	parse_file(fd, map);
	close(fd);
}
