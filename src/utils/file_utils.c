/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybutkov <ybutkov@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/29 14:01:51 by ybutkov           #+#    #+#             */
/*   Updated: 2026/01/29 14:20:46 by ybutkov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "constants.h"
#include "libft.h"
#include <fcntl.h>
#include <stdlib.h>

int	has_extension(const char *filename, const char *extension)
{
	size_t	len;
	size_t	ext_len;

	if (!filename || !extension)
		return (NO);
	len = ft_strlen(filename);
	ext_len = ft_strlen(extension);
	if (len < ext_len)
		return (NO);
	if (ft_strcmp(&filename[len - ext_len], extension) == 0)
		return (OK);
	return (NO);
}

int	try_open_file(const char *filename)
{
	int	fd;

	fd = open(filename, O_RDONLY);
	if (fd < 0)
		return (close(fd), NO);
	close(fd);
	return (OK);
}
