/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bvh_core.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybutkov <ybutkov@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/11 00:00:49 by ybutkov           #+#    #+#             */
/*   Updated: 2026/01/26 00:50:58 by ybutkov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "bvh_internal.h"

t_obj	**convert_list_to_array(t_obj *obj, int amount)
{
	t_obj	**obj_array;
	int		i;

	obj_array = malloc(amount * sizeof(t_obj *));
	if (obj_array == NULL)
		return (NULL);
	i = 0;
	while (obj && i < amount)
	{
		obj_array[i] = obj;
		obj = obj->next;
		i++;
	}
	return (obj_array);
}

static int	setup_bvh_with_planes(t_bvh_data *data, int amount)
{
	data->bvh->root = create_bvh_node(create_infinite_aabb(), data->obj,
			data->plane_count + amount);
	if (data->bvh->root == NULL)
	{
		free(data->arr);
		return (NO);
	}
	if (data->plane_count > 0)
		data->bvh->root->left = create_bvh_node(create_infinite_aabb(),
				data->obj, data->plane_count);
	data->bvh->root->right = create_bvh_node(calculate_aabb_array(data->arr,
				amount), data->arr[0], amount);
	if (data->plane_count > 0 && data->bvh->root->left)
		data->bvh->root->left->is_leaf = OK;
	if (data->bvh->root->right)
		generate_bvh_node(data->bvh->root->right, data->arr, amount);
	free(data->arr);
	return (OK);
}

int	generate_bvh(t_bvh *bvh, t_obj *obj)
{
	t_bvh_data	data;
	t_obj		*first_non_plane;
	int			amount;

	first_non_plane = move_planes_to_head(&obj);
	data.plane_count = count_planes(obj, first_non_plane);
	if (!first_non_plane)
		return (handle_only_planes(bvh, obj, data.plane_count));
	amount = get_obj_count(first_non_plane);
	if (amount == 0)
		return (OK);
	data.arr = convert_list_to_array(first_non_plane, amount);
	if (data.arr == NULL)
		return (NO);
	data.bvh = bvh;
	data.obj = obj;
	return (setup_bvh_with_planes(&data, amount));
}

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
			free_texture(mlx, (t_texture *)obj->texture);
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

t_bvh	*create_bvh(void)
{
	t_bvh	*bvh;

	bvh = malloc(sizeof(t_bvh));
	if (bvh == NULL)
		return (HANDLE_ERROR_NULL);
	bvh->mlx = NULL;
	bvh->build = generate_bvh;
	bvh->free = free_bvh;
	return (bvh);
}
