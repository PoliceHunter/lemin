/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   addapt_vector.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksean <ksean@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/06 23:30:32 by ksean             #+#    #+#             */
/*   Updated: 2020/11/06 23:30:40 by ksean            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

t_vector	new_node_vec(size_t capacity)
{
	return (new_vector(capacity, sizeof(t_node)));
}

t_node		*get_from_node_vec(t_vector *vec, size_t index)
{
	return ((t_node *)get_from_vec(vec, index));
}

t_character	get_character(t_vector *vec)
{
	int			index;
	t_node		*node;
	t_character	result;

	result.target = NULL;
	result.root = NULL;
	index = 0;
	while (index < vec->size)
	{
		node = get_from_node_vec(vec, index++);
		if (node->is_start_node)
			result.root = node;
		else if (node->is_end_node)
			result.target = node;
		if (result.root != NULL && result.target != NULL)
			return (result);
	}
	return (result);
}

void		push_back_node_vec(t_vector *vec, t_node node)
{
	return (push_back_vec(vec, &node));
}

void		push_front_node_vec(t_vector *vec, t_node node)
{
	return (push_front_vec(vec, &node));
}
