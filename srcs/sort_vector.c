/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_vector.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksean <ksean@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/06 22:26:34 by ksean             #+#    #+#             */
/*   Updated: 2020/11/06 23:27:41 by ksean            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

int			cmp_node(t_vector *vec, size_t index1, t_node *new_node)
{
	return (ft_strcmp(get_from_node_vec(vec, index1)->name, new_node->name));
}

static int	ret(size_t start, size_t end, t_node new_node, t_vector *vec)
{
	size_t pivot;

	pivot = ((end - start) / 2) + start;
	if (cmp_node(vec, pivot, &new_node) == 0)
		return (pivot);
	if (cmp_node(vec, pivot, &new_node) > 0)
		return (insert_with_sort_node_internal(vec, start, pivot + 1,
		new_node));
	else
		return (insert_with_sort_node_internal(vec, pivot - 1, vec->size,
		new_node));
}

int			insert_with_sort_node_internal(t_vector *vec, size_t start,
			size_t end, t_node new_node)
{
	size_t i;

	i = start;
	if (start == end)
	{
		push_back_node_vec(vec, new_node);
		return (vec->size - 1);
	}
	if (end - start <= 3)
	{
		while (i != end)
		{
			if (cmp_node(vec, i, &new_node) > 0)
			{
				insert_into_vec(vec, i, &new_node);
				return (i);
			}
			i++;
		}
		push_back_node_vec(vec, new_node);
		return (vec->size - 1);
	}
	return (ret(start, end, new_node, vec));
}

int			insert_with_sort_node(t_vector *vec, t_node new_node)
{
	return (insert_with_sort_node_internal(vec, 0, vec->size, new_node));
}

int			is_sorted(t_vector vec)
{
	int i;

	i = -1;
	while (++i < vec.size - 1)
		if (ft_strcmp(get_from_node_vec(&vec, i)->name,
			get_from_node_vec(&vec, i + 1)->name) > 0)
			return (0);
	return (1);
}
