/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vectors.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybutkov <ybutkov@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/03 19:26:58 by ybutkov           #+#    #+#             */
/*   Updated: 2026/01/03 19:49:32 by ybutkov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VECTORS_H
# define VECTORS_H

typedef struct s_vec3
{
	double	x;
	double	y;
	double	z;
}			t_vec3;

t_vec3		create_vector(double x, double y, double z);
t_vec3		vector_add(t_vec3 v1, t_vec3 v2);
t_vec3		vector_sub(t_vec3 v1, t_vec3 v2);
double		vector_dot_product(t_vec3 v1, t_vec3 v2);
double		vector_length(t_vec3 v1);
t_vec3		vector_norm(t_vec3 v1);
t_vec3		vector_cross(t_vec3 v1, t_vec3 v2);

#endif
