/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_cross.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmyrcell <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/28 22:54:50 by tmyrcell          #+#    #+#             */
/*   Updated: 2020/11/28 22:54:51 by tmyrcell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

int		is_in_way(t_way *way, t_node_ptr *search)
{
	int			j;
	t_node_ptr	*node;

	j = 0;
	while (++j < way->nodes.size - 1)
	{
		node = get_from_vec(&way->nodes, j);
		if (*node == *search)
			return (TRUE);
	}
	return (FALSE);
}

int		is_cross(t_vector *ways)
{
	t_node_ptr	*node;
	t_way		*way;
	int			i;
	int			j;
	t_way		*last;

	i = -1;
	j = 0;
	if (ways->size < 2)
		return (FALSE);
	last = get_last_way(ways);
	if (last == NULL)
		return (FALSE);
	while (++i < ways->size - 1)
	{
		way = get_from_vec(ways, i);
		while (++j < way->nodes.size - 1)
		{
			node = get_from_vec(&way->nodes, j);
			if (is_in_way(last, node))
				return (TRUE);
		}
	}
	return (FALSE);
}
