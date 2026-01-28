/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybutkov <ybutkov@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/31 21:34:14 by skomyshe          #+#    #+#             */
/*   Updated: 2026/01/28 22:53:00 by ybutkov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include "miniRT.h"
#include "parser.h"
#include <fcntl.h>
#include <string.h>
#include <unistd.h>
#include <mlx.h>

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
				ft_memmove(&line[i + 1], &line[j], ft_strlen(&line[j]) + 1);
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
	printf("data_rule.data_type=%s\n", data_rule.data_type);
	if (ft_strcmp(data_rule.data_type, "UNKHOWN") == 0
		|| data_rule.create(data_rule, tokens, map) == NO)
		return (free_split(tokens), PARSE_INVALID_FORMAT);
	free_split(tokens);
	printf("3_1\n");
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
	printf("1_1\n");
	normalize_line(line);
	printf("2_1\n");
	return (process_tokens(line, map));
}

void	parse_file(int fd, t_map *map)
{
	char			*line;
	int				line_num;
	t_parse_error	err;
	void			*mlx;

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
			mlx = map->mlx;
			map->free(map);
			mlx_destroy_display(mlx);
			free(mlx);
			parse_error_exit(err, line_num, line);
		}
		free(line);
		printf("4_1\n");
		line = get_next_line(fd);
	}
}

void	parse_scene(const char *filename, t_map *map)
{
	int	fd;

	fd = open(filename, O_RDONLY);
	if (fd < 0)
		error_exit("Failed to open file", map);
	parse_file(fd, map);
	close(fd);
}
