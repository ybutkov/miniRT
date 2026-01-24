/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybutkov <ybutkov@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/04 01:53:26 by skomyshe          #+#    #+#             */
/*   Updated: 2026/01/24 20:53:02 by ybutkov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

# include "constants.h"
# include "objects.h"
# include "miniRT.h"

# define MAX_AMOUNT_DATA_TYPE 7
# define AMOUNT_DATA_RULE 11

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
	int			(*create)(struct s_data_rule rule, char	**tokens, t_map *map);
}				t_data_rule;

t_data_rule		get_data_rule(char *obj_type);
int				parser_color(char *str, t_color *c);
int				get_valid_color_part(const char *s);
int				parser_vec3(char *str, t_vec3 *vector);
int				get_valid_float(const char *str, float *res);

#endif