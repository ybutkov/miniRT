/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   constants.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybutkov <ybutkov@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/03 17:28:55 by ybutkov           #+#    #+#             */
/*   Updated: 2026/01/24 20:18:57 by ybutkov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CONSTANTS_H

# define CONSTANTS_H

# include <math.h>

# ifndef M_PI
#  define M_PI 3.14159265358979323846
# endif

# define OK 1
# define NO 0
# define HANDLE_ERROR_NULL NULL
# define ERROR_MSG_ARGS "Error. There should be one argument - file name *.rt"

# define DEFAULT_BRIGHTNESS 1
# define DEFAULT_REFLECTION 0.0
# define EPSILON 1e-4
# define DEGREE_TO_RAD (2.0 * M_PI / 360.0)
# define ROTATE_CAMERA_STEP 2
# define MOVE_CAMERA_STEP 1

# define AXIS_LENGTH 40
# define AXIS_OFFSET_X 80
# define AXIS_OFFSET_Y 80

#endif