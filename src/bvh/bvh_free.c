/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bvh_free.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybutkov <ybutkov@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/26 21:17:35 by ybutkov           #+#    #+#             */
/*   Updated: 2026/01/26 21:17:59 by ybutkov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "bvh_internal.h"

static void	free_objects_from_node(t_bvh_node *node, void *mlx)
{
	t_obj	*obj;
	t_obj	*next;
	int		i;

	if (!node || !node->obj)
		return ;
	obj = node->obj;
	i = 0;
	while (obj && i < node->amount_obj)
	{
		next = obj->next;
		if (obj->data)
			free(obj->data);
		if (obj->texture)
		{
			if (obj->texture_type == TEXTURE_FILE)
				free_texture(mlx, (t_texture *)obj->texture);
			else if (obj->texture_type == TEXTURE_CHESS)
				free(obj->texture);
		}
		free(obj);
		obj = next;
		i++;
	}
}

static void	free_bvh_node(t_bvh_node *node, void *mlx)
{
	if (!node)
		return ;
	free_bvh_node(node->left, mlx);
	free_bvh_node(node->right, mlx);
	if (node->is_leaf && node->obj)
		free_objects_from_node(node, mlx);
	free(node);
}

void	free_bvh(t_bvh *this)
{
	if (!this)
		return ;
	if (this->root)
		free_bvh_node(this->root, this->mlx);
	free(this);
}
