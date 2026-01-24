/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybutkov <ybutkov@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/31 21:34:14 by skomyshe          #+#    #+#             */
/*   Updated: 2026/01/24 18:44:41 by ybutkov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include "miniRT.h"
#include "parser.h"
#include <fcntl.h>
#include <string.h>
#include <unistd.h>

void	exit_with_tokens(char **tokens, t_map *map, const char *msg)
{
	if (tokens)
		free_split(tokens);
	error_exit(msg, map);
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

t_parse_error	parse_line_new(char *line, t_map *map)
{
	size_t		len;
	char		**tokens;
	t_data_rule	data_rule;

	if (line)
	{
		len = ft_strlen(line);
		if (len > 0 && line[len - 1] == '\n')
			line[len - 1] = '\0';
	}
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

void	parse_file(int fd, t_map *map)
{
	char			*line;
	int				line_num;
	t_parse_error	err;

	line_num = 0;
	while ((line = get_next_line(fd)))
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
