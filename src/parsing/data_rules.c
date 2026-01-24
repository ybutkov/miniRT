/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   data_rules.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybutkov <ybutkov@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/22 15:25:54 by ybutkov           #+#    #+#             */
/*   Updated: 2026/01/24 19:56:17 by ybutkov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "parser.h"

static int	create_mock(t_data_rule rule, char **tokens, t_map *map)
{
	(void)rule;
	(void)tokens;
	(void)map;
	return (OK);
}

static t_data_rule	*get_data_rules(void)
{
	static t_data_rule	data_rules[AMOUNT_DATA_TYPE + 1];
	static int			init;

	if (!init)
	{
		data_rules[0] = (t_data_rule){"UNKHOWN", {}, 0, 0, NULL};
		data_rules[1] = (t_data_rule){"#", {}, 0, 0, create_mock};
		data_rules[2] = (t_data_rule){"A", {FLOAT, COLOR}, 2, 2, create_a};
		data_rules[3] = (t_data_rule){"C", {VEC3, VEC3, INT}, 3, 3, create_c};
		data_rules[4] = (t_data_rule){"L", {VEC3, FLOAT, COLOR}, 3, 2,
			create_l};
		data_rules[5] = (t_data_rule){"sp", {VEC3, FLOAT, COLOR, FLOAT}, 4, 3,
			create_sp};
		data_rules[6] = (t_data_rule){"pl", {VEC3, VEC3, COLOR, FLOAT}, 4, 3,
			create_pl};
		data_rules[7] = (t_data_rule){"cy", {VEC3, VEC3, FLOAT, FLOAT, COLOR,
			FLOAT}, 6, 5, create_cy};
		data_rules[8] = (t_data_rule){"tr", {VEC3, VEC3, VEC3, COLOR, FLOAT}, 5,
			4, create_tr};
		data_rules[9] = (t_data_rule){"box", {VEC3, VEC3, VEC3, COLOR, FLOAT},
			5, 4, create_b};
		init = 1;
	}
	return (data_rules);
}

t_data_rule	get_data_rule(char *obj_type)
{
	int	i;

	i = 1;
	while (i < AMOUNT_DATA_TYPE)
	{
		if (ft_strcmp(obj_type, get_data_rules()[i].data_type) == 0)
			return (get_data_rules()[i]);
		++i;
	}
	return (get_data_rules()[0]);
}
