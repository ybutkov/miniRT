/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybutkov <ybutkov@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/31 16:38:02 by ybutkov           #+#    #+#             */
/*   Updated: 2026/01/18 00:18:52 by ybutkov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAP_H

# define MAP_H

# include "point.h"
# include "objects.h"
# include "bvh.h"
# include <stddef.h>

typedef enum e_projection
{
	PROJ_ISO,
	PROJ_PARALLEL
}					t_projection;

typedef struct s_map
{
//
	t_obj			*objects;
	t_camera		*camera;
	t_ambient		*ambient;
	t_light			*lights;
	t_bvh			*bvh;
//
	int				width;
	int				height;
	double			zoom;
	double			z_scale;
	double			rotation_x;
	double			rotation_y;
	double			rotation_z;
	int				offset_x;
	int				offset_y;
	int				shift_size;
	int				zoom_size;
	int				is_change;
	t_projection	projection;

	void			(*free)(struct s_map *map);
	void			(*reset)(struct s_map *map);
	void			(*shift)(struct s_map *map, int x, int y);
	void			(*zoom_in)(struct s_map *map, int delta);
	void			(*add_obj)(struct s_map *map, t_obj *object);
	int				(*generate_bvh)(t_map *map);
	void			(*add_light)(struct s_map *map, t_light *light);
}					t_map;

typedef struct s_img
{
	void			*img;
	char			*addr;
	int				bits_per_pixel;
	int				line_length;
	int				endian;
}					t_img;

t_map				*create_map(size_t width, size_t height);

#endif
