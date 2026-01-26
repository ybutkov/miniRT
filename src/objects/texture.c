/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybutkov <ybutkov@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/25 00:00:00 by ybutkov           #+#    #+#             */
/*   Updated: 2026/01/26 19:07:32 by ybutkov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "constants.h"
#include "objects.h"
#include "parser.h"
#include "mlx.h"
#include "libft.h"
#include <stdlib.h>
#include <math.h>

t_texture	*load_texture(void *mlx, char *path)
{
	t_texture	*texture;

	if (!mlx || !path)
		return (NULL);
	texture = malloc(sizeof(t_texture));
	if (!texture)
		return (NULL);
	texture->img = mlx_xpm_file_to_image(mlx, path, &texture->width,
			&texture->height);
	if (!texture->img)
	{
		free(texture);
		return (NULL);
	}
	texture->addr = mlx_get_data_addr(texture->img, &texture->bpp,
			&texture->line_len, &texture->endian);
	return (texture);
}

void	free_texture(void *mlx, t_texture *texture)
{
	if (!texture)
		return ;
	if (texture->img && mlx)
		mlx_destroy_image(mlx, texture->img);
	free(texture);
}

t_color	get_texture_color(t_texture *tex, double u, double v)
{
	int		x;
	int		y;
	int		color_int;
	char	*pixel;

	if (!tex || !tex->addr)
		return (create_color(255, 255, 255));
	u = fmod(u, 1.0);
	v = fmod(v, 1.0);
	if (u < 0)
		u += 1.0;
	if (v < 0)
		v += 1.0;
	x = (int)(u * tex->width) % tex->width;
	y = (int)(v * tex->height) % tex->height;
	pixel = tex->addr + (y * tex->line_len + x * (tex->bpp / 8));
	color_int = *(int *)pixel;
	return (create_color((color_int >> 16) & 0xFF, (color_int >> 8) & 0xFF,
			color_int & 0xFF));
}

void	get_sphere_uv(t_vec3 point, t_vec3 center, double *u, double *v)
{
	t_vec3	p;
	double	theta;
	double	phi;

	p = vector_norm(vector_sub(point, center));
	theta = acos(-p.y);
	phi = atan2(-p.z, p.x) + M_PI;
	*u = phi / (2.0 * M_PI);
	*v = 1.0 - (theta / M_PI);
}

t_color	get_chess_color(t_chess_texture *chess, double u, double v, t_color color1)
{
	int	pattern;

	u = fmod(u * chess->scale, 1.0);
	v = fmod(v * chess->scale, 1.0);
	if (u < 0)
		u += 1.0;
	if (v < 0)
		v += 1.0;
	pattern = ((int)(u * 2.0) + (int)(v * 2.0)) % 2;
	if (pattern == 0)
		return (chess->color2);
	return (color1);
}

t_chess_texture	*create_chess_texture(char *color_str, char *scale_str)
{
	t_chess_texture	*chess;
	float			scale;

	if (!color_str || !scale_str)
		return (NULL);
	chess = malloc(sizeof(t_chess_texture));
	if (!chess)
		return (HANDLE_ERROR_NULL);
	if (parser_color(color_str, &chess->color2) == NO
		|| get_valid_float(scale_str, &scale) == NO)
	{
		free(chess);
		return (NULL);
	}
	chess->scale = (double)scale;
	return (chess);
}

t_color	default_get_color(t_obj *obj, t_vec3 hit_point)
{
	(void)hit_point;
	return (obj->color);
}
