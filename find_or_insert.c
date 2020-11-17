/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_or_insert.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksean <ksean@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/06 23:30:58 by ksean             #+#    #+#             */
/*   Updated: 2020/11/06 23:31:22 by ksean            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

int		find_in_vec_internal(t_vector *vec, int start, int end,
		char *name)
{
	int		i;
	int 	pivot;
	int		compare;

	i = start - 1;
	if (start == end)
		return (ft_strcmp(get_from_node_vec(vec, start)->name, name) == 0)
		? (int)start : -1;
	if (end - start <= 3)
	{
		while (++i != end)
		{
			if (ft_strcmp(get_from_node_vec(vec, i)->name, name) == 0)
				return (i);
		}
		return (-1);
	}
	pivot = ((end - start) / 2) + start;
	compare = ft_strcmp(get_from_node_vec(vec, pivot)->name, name);
	if (compare == 0)
		return (pivot);
	else if (compare > 0)
		return (find_in_vec_internal(vec, start, pivot, name));
	else
		return (find_in_vec_internal(vec, pivot + 1, vec->size, name));
}

int		find_in_vec(t_vector *vec, const char *name)
{
	if (vec->size == 0)
		return (-1);
	return (find_in_vec_internal(vec, 0, vec->size, (char *)name));
}

t_node	*find_and_get(t_vector *vec, char *name)
{
	int index;

	index = find_in_vec(vec, name);
	if (vec->size == 0)
		return (NULL);
	if (index == -1)
		return (NULL);
	return (get_from_node_vec(vec, index));
}

t_node	*find_or_insert(t_vector *vec, const char *new_node)
{
	int		index;
	t_node	node;

	index = find_in_vec(vec, new_node);
	if (index == -1)
	{
		node = init_node(new_node);
		index = insert_with_sort_node(vec, node);
	}
	return (get_from_node_vec(vec, index));
}
