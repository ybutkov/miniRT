/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vectors.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybutkov <ybutkov@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/03 19:26:58 by ybutkov           #+#    #+#             */
/*   Updated: 2026/01/11 00:36:07 by ybutkov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VECTORS_H
# define VECTORS_H

typedef struct s_vec
{
	union
	{
		struct
		{
			double	x;
			double	y;
			double	z;
		};
		struct
		{
			double	r;
			double	g;
			double	b;
		};
		double		v[3];
	};
}					t_vec3;
t_vec3				create_vector(double x, double y, double z);
t_vec3				vector_add(t_vec3 v1, t_vec3 v2);
t_vec3				vector_sub(t_vec3 v1, t_vec3 v2);
t_vec3				vector_mult(t_vec3 v1, double scalar);
t_vec3				vector_add_scalar(t_vec3 v1, double sc);
t_vec3				vector_sub_scalar(t_vec3 v1, double sc);
double				vector_dot_product(t_vec3 v1, t_vec3 v2);
double				vector_length(t_vec3 v1);
t_vec3				vector_norm(t_vec3 v1);
t_vec3				vector_cross(t_vec3 v1, t_vec3 v2);
t_vec3				vector_reflect(t_vec3 ray, t_vec3 normal);
t_vec3				vector_rotate_axis(t_vec3 v, t_vec3 axis, double angle);
t_vec3				vector_min(t_vec3 v1, t_vec3 v2);
t_vec3				vector_max(t_vec3 v1, t_vec3 v2);

#endif
