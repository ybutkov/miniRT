/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   data_rules.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybutkov <ybutkov@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/22 15:25:54 by ybutkov           #+#    #+#             */
/*   Updated: 2026/01/22 22:31:14 by ybutkov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include "libft.h"

static t_data_rule	*get_data_rules(void)
{
	static t_data_rule	data_rules[AMOUNT_DATA_TYPE + 1];
	static int			init;

	if (!init)
	{
		data_rules[0] = (t_data_rule){"UNKHOWN", {}, 0, 0};
		data_rules[1] = (t_data_rule){"A", {FLOAT, COLOR}, 2, 2};
		data_rules[2] = (t_data_rule){"C", {VEC3, VEC3, INT}, 3, 3};
		data_rules[3] = (t_data_rule){"L", {VEC3, FLOAT, COLOR}, 3, 3};
		data_rules[4] = (t_data_rule){"sp", {VEC3, FLOAT, COLOR, FLOAT}, 4, 3};
		data_rules[5] = (t_data_rule){"pl", {VEC3, VEC3, COLOR, FLOAT}, 4, 3};
		data_rules[6] = (t_data_rule){"cy", {VEC3, VEC3, FLOAT, FLOAT, COLOR,
			FLOAT}, 6, 5};
		data_rules[7] = (t_data_rule){"tr", {VEC3, VEC3, VEC3, COLOR, FLOAT},
			5, 4};
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
