/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybutkov <ybutkov@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/25 00:00:00 by ybutkov           #+#    #+#             */
/*   Updated: 2026/01/25 16:38:57 by ybutkov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "constants.h"
#include "objects.h"
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

t_color	sphere_get_color(t_obj *obj, t_vec3 hit_point)
{
	t_texture	*tex;
	t_sphere	*sphere;
	double		u;
	double		v;
	t_color		tex_color;

	if (!obj->texture || obj->texture_intensity <= 0.0)
		return (obj->color);
	tex = (t_texture *)obj->texture;
	sphere = (t_sphere *)obj->data;
	get_sphere_uv(hit_point, sphere->center, &u, &v);
	tex_color = get_texture_color(tex, u, v);
	return (color_mix(obj->color, tex_color, obj->texture_intensity));
}

t_color	default_get_color(t_obj *obj, t_vec3 hit_point)
{
	(void)hit_point;
	return (obj->color);
}
