/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reset_states.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmyrcell <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/28 22:51:45 by tmyrcell          #+#    #+#             */
/*   Updated: 2020/11/28 22:51:46 by tmyrcell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void	reset_edge(t_edge *edge)
{
	if (edge->mark == MARK_DISABLE)
	{
		edge->capacity = 0;
		edge->backward->capacity = 0;
		return ;
	}
	edge->capacity = edge->original_capacity;
	edge->backward->capacity = edge->backward->original_capacity;
	edge->mark = MARK_NONE;
}

void	reset_state(t_vector *nodes, int except_mark)
{
	t_node_ptr	ptr;
	int			index;

	index = -1;
	while (++index < nodes->size)
	{
		ptr = get_from_node_vec(nodes, index);
		if (ptr->traversal_state != except_mark)
			ptr->traversal_state = STATE_NO_INVOLVED;
		ptr->bfs = 0;
		remove_all_not_free(&ptr->ants);
	}
}

void	reset_all_edges(t_vector *nodes)
{
	t_edge		*edge;
	t_node_ptr	node;
	int			way_i;
	int			i;

	way_i = -1;
	while (++way_i != nodes->size)
	{
		node = get_from_vec(nodes, way_i);
		i = -1;
		while (++i != node->links.size)
		{
			edge = get_from_vec(&node->links, i);
			reset_edge(edge);
		}
	}
}

int		reset_all_states(t_vector *nodes)
{
	reset_state(nodes, STATE_NONE);
	return (TRUE);
}

int		refresh_state(t_vector *ways, t_vector *nodes)
{
	t_way *way;

	while (ways->size != 0)
	{
		way = pop_back_vec(ways);
		free_vec(&way->nodes);
		free_vec(&way->edges);
		free(way);
	}
	reset_all_states(nodes);
	reset_all_edges(nodes);
	return (0);
}
