/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   miniRT.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skomyshe <skomyshe@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/31 16:23:11 by ybutkov           #+#    #+#             */
/*   Updated: 2026/01/02 19:48:29 by skomyshe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_H

# define MINIRT_H

# include "hooks.h"
# include "libft.h"
# include "map.h"
# include "mouse.h"
# include <math.h>
# include <mlx.h>
# include <stdint.h>
# include <stdio.h>
# include <stdlib.h>

# define WINDOW_WIDTH 1920
# define WINDOW_HEIGHT 1080
# define INFO_PANEL_WIDTH 400
# define MIN_TIME_FRAMES 16 // calculate time for render and change?
# define SHIFT_SIZE 10
# define ZOOM_SIZE_PERCENT 5

typedef struct s_key_actions	t_key_actions;

typedef struct s_atof
{
	float		res;
	float		sign;
	float		f;
	int			dot_count;
}				t_atof;

typedef struct s_app
{
	void						*mlx;
	void						*win;
	size_t						width;
	size_t						height;
	t_map						*map;
	t_img						*img;
	long int					last_frame_time;
	t_mouse_state				mouse;
	t_key_actions				*key_actions;

	void						(*free)(struct s_app *app);
	void						(*render)(struct s_app *app);
	void						(*clear_image)(t_img *img);
}								t_app;

// Vector and Color
typedef struct s_vec3
{
	double						x;
	double						y;
	double						z;
}								t_vec3;

typedef struct s_color
{
	int							r;
	int							g;
	int							b;
}								t_color;

// elements
typedef struct s_ambient
{
	double						ratio;
	t_color						color;
}								t_ambient;

typedef struct s_camera
{
	t_vec3						pos;
	t_vec3						dir;
	int							fov;
}								t_camera;

typedef struct s_light
{
	t_vec3						pos;
	double						ratio;
	t_color						color;
}								t_light;

// objs
typedef enum e_obj_type
{
	SPHERE,
	PLANE,
	CYLINDER
}								t_obj_type;

typedef struct s_object
{
	t_obj_type					type;
	t_vec3						pos;
	t_vec3						dir;
	double						diameter;
	double						height;
	t_color						color;
	struct s_object				*next;
}								t_object;

// scene
typedef struct s_scene
{
	t_ambient					*ambient;
	t_camera					*camera;
	t_light						*light;
	t_object					*objects;
}								t_scene;

// Scene helpers
void							init_scene(t_scene *scene);
void							print_scene(t_scene *scene);
void							free_scene(t_scene *scene);

// --- Parsing functions
void							parse_line(char *line, t_scene *scene);
void							parse_scene(const char *filename,
									t_scene *scene);
void							parse_ambient(char **tokens, t_scene *scene);
void							parse_camera(char **tokens, t_scene *scene);
void							parse_light(char **tokens, t_scene *scene);
void							parse_sphere(char **tokens, t_scene *scene);
void							parse_plane(char **tokens, t_scene *scene);
void							parse_cylinder(char **tokens, t_scene *scene);

void							parse_line(char *line, t_scene *scene);

// Parsing helpers
t_vec3							parse_vec3(char *str);
t_color							parse_color(char *str);
void							check_normalized(t_vec3 v);

// Parsing atof
void							parse_number(const char *str, t_atof *atof, int *i);
float							ft_atof(const char *str);

// Error
// void							ft_error(t_scene *scene);
void							ft_error(void);

void							error_exit(char *msg);
void							free_split(char **split);
int								ft_split_len(char **split);
// double							ft_atof(const char *str);

t_app							*create_app(t_map *map);

#endif
