/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ptr_list.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybutkov <ybutkov@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/11 19:32:35 by ybutkov           #+#    #+#             */
/*   Updated: 2026/01/11 20:37:33 by ybutkov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stddef.h>

int	ptr_list_length(void *list)
{
	int		len;
	void	**ptr;

	if (!list)
		return (0);
	len = 0;
	ptr = (void **)list;
	while (ptr[len] != NULL)
		len++;
	return (len);
}
