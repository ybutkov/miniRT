/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   miniRT.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybutkov <ybutkov@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/31 16:23:11 by ybutkov           #+#    #+#             */
/*   Updated: 2026/01/28 16:53:36 by ybutkov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_H

# define MINIRT_H

# include "colors.h"
# include "hooks.h"
# include "libft.h"
# include "map.h"
# include "mouse.h"
# include "objects.h"
# include "rays.h"
# include "vectors.h"
# include <math.h>
# include <mlx.h>
# include <stdint.h>
# include <stdio.h>
# include <stdlib.h>

# define WINDOW_WIDTH 1080 // 1920
# define WINDOW_HEIGHT 572 // 1080
# define INFO_PANEL_WIDTH 400
# define MIN_TIME_FRAMES 16 // calculate time for render and change?
# define SHIFT_SIZE 1
# define ZOOM_SIZE_PERCENT 1
# define REFLECTION_AMOUNT 5
# define REFLECTION_DEFAULT 0

typedef struct s_key_actions	t_key_actions;

typedef enum e_parse_error
{
	PARSE_OK = 0,
	PARSE_EMPTY_LINE,
	PARSE_UNKNOWN_ID,
	PARSE_INVALID_FORMAT,
	PARSE_MALLOC_FAIL
}								t_parse_error;

typedef struct s_atof
{
	float						res;
	float						sign;
	float						f;
	int							dot_count;
}								t_atof;

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
	t_obj						*selected_obj;

	void						(*free)(struct s_app *app);
	void						(*render)(struct s_app *app);
	void						(*clear_image)(t_img *img);
}								t_app;

void							print_map(t_map *map);

// --- Parsing functions
void							parse_scene(const char *filename, t_map *map);

// Parsing helpers
t_vec3							parse_vec3(char *str);
t_color							parse_color(char *str);
void							check_normalized(t_vec3 v);

// Parsing atof
int								is_validate_real(const char *str);
float							ft_atof(const char *str);

// Free function
void							free_object_list(t_obj *objects);

void							exit_with_tokens(char **tokens, t_map *map,
									const char *msg);
void							error_exit(const char *msg, t_map *map);
void							free_split(char **split);
int								ft_split_len(char **split);

// draw
void							ft_mlx_pixel_put(t_img *img, int x, int y,
									int color);
void							ft_mlx_pixel_put_safe(t_img *img, int x, int y,
									int color);
t_app							*create_app(t_map *map);
void							parse_error_exit(t_parse_error err,
									int line_num, char *line);

void							parse_file(int fd, t_map *map);
void							parse_error_exit(t_parse_error err,
									int line_num, char *line);
t_parse_error					parse_line(char *line, t_map *map);

t_obj							*select_object_at_screen_pos(t_app *app,
									int screen_x, int screen_y);
void							move_selected_object(t_app *app, int delta_x,
									int delta_y);

#endif
