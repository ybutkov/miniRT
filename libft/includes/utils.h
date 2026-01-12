/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybutkov <ybutkov@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/08 13:59:35 by ybutkov           #+#    #+#             */
/*   Updated: 2026/01/11 19:41:53 by ybutkov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_H
# define UTILS_H

# include <stdlib.h>

long int		get_time_in_milliseconds(void);
int				between(long long value, long long left, long long right);
int				in_set(char ch, char *set);
unsigned int	hash(char *key);
int             ptr_list_length(void *list);

#endif