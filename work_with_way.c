/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   work_with_way.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmyrcell <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/14 13:23:20 by tmyrcell          #+#    #+#             */
/*   Updated: 2020/11/14 13:23:22 by tmyrcell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

int		is_skip_in_reconstruction(t_edge *edge, t_node_ptr src)
{
	if (edge->capacity == 0)
		return (TRUE);
	if (edge->dst->bfs == 1)
	{
		if (edge->backward->dst->is_start_node != 1)
			return (TRUE);
	}
	if (edge->backward->dst->is_cross && edge->backward->capacity == 0)
		return (edge->mark != MARK_BACKWARD_PATH);
	return (edge->backward->dst->bfs != src->bfs - 1 ||
			edge->backward->dst->traversal_state != STATE_VISITED);
}

void	set_bfs_children(t_vector *queue, t_node_ptr current) ///27/25
{
	t_edge	*edge;
	int		i;

	i = -1;
	while (++i < current->links.size)
	{
		edge = get_from_vec(&current->links, i);
		if (edge->capacity == 0)
			continue ;
		if (current->is_cross && edge->mark != MARK_BACKWARD_PATH)
			continue ;
		if (edge->dst->traversal_state == STATE_IN_PATH
			&& is_have_reverse_edge(edge->dst))
		{
			if (edge->dst->bfs != 0)
				continue ;
			edge->dst->bfs = current->bfs + 1;
			edge->dst->is_first_cross = TRUE;
			push_back_vec(queue, &edge->dst);
			continue ;
		}
		if (edge->dst->traversal_state != STATE_NO_INVOLVED)
			continue ;
		edge->dst->bfs = current->bfs + 1;
		edge->dst->traversal_state = STATE_IN_QUEUE;
		push_back_vec(queue, &edge->dst);
	}
}

void	finish_reconstruct(t_way *way, t_edge *edge, t_vector *nodes)
{
	push_front_vec(&way->nodes, &edge->backward->dst);
	direct_and_mark_way_edges(way);
	reset_state(nodes, STATE_IN_PATH);
}

int		reconstruct_way(t_node_ptr ptr, t_way *way, t_vector *nodes) ///27/25
{
	t_edge	*edge;
	int		i;

	*way = init_way();
	i = -1;
	while (++i < ptr->links.size)
	{
		edge = get_from_vec(&ptr->links, i);
		edge = edge->backward;
		ft_assert(edge != NULL, "Edges corrupted");
		if (is_skip_in_reconstruction(edge, ptr) == TRUE)
			continue ;
		edge->dst->traversal_state = STATE_IN_PATH;
		push_front_vec(&way->nodes, &ptr);
		push_front_vec(&way->edges, &edge);
		if (edge->mark == MARK_BACKWARD_PATH ||
		edge->backward->dst->is_first_cross == TRUE)
			way->state = IS_CROSS;
		ptr = edge->backward->dst;
		i = -1;
		if (edge->backward->dst->is_start_node)
		{
			finish_reconstruct(way, edge, nodes);
			return (TRUE);
		}
	}
	return (FALSE);
}

int		find_by_bfs(t_node_ptr src, t_way *way, t_vector *nodes)
{
	t_node_ptr	*current;
	t_vector	queue;

	queue = new_vector(10, sizeof(t_node_ptr));
	push_back_vec(&queue, &src);
	while (queue.size != 0)
	{
		current = pop_front_vec(&queue);
		if ((*current)->traversal_state == STATE_VISITED)
			continue ;
		if ((*current)->is_end_node)
		{
			free_vec(&queue);
			return (reconstruct_way(*current, way, nodes));
		}
		if ((*current)->traversal_state == STATE_IN_PATH)
			(*current)->is_cross = TRUE;
		(*current)->traversal_state = STATE_IN_QUEUE;
		set_bfs_children(&queue, *current);
		(*current)->traversal_state = STATE_VISITED;
		free(current);
	}
	free_vec(&queue);
	return (FALSE);
}

