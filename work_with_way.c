/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   work_with_way.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmyrcell <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/14 13:23:20 by tmyrcell          #+#    #+#             */
/*   Updated: 2020/11/28 22:51:27 by tmyrcell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void		set_bfs_children(t_queue **queue, t_node_ptr current)
{
	t_edge	*edge;
	t_edge	*backward_edge;
	int		i;

	i = -1;
	while (++i < current->links.size)
	{
		edge = get_from_vec(&current->links, i);
		if (edge->capacity == 0)
			continue ;
		if (edge->dst->traversal_state == STATE_IN_PATH && (backward_edge =
				get_reverse_edge(edge->dst, STATE_IN_PATH)) != NULL)
		{
			if (edge->dst->traversal_state == STATE_VISITED)
				continue ;
			edge->dst->bfs = current->bfs + 1;
			edge->dst->traversal_state = STATE_IN_CROSS;
			if (backward_edge->dst->traversal_state == STATE_IN_PATH)
				queue_up(queue, backward_edge->dst, current->bfs + 2);
			continue ;
		}
		if (edge->dst->traversal_state != STATE_NO_INVOLVED)
			continue ;
		queue_up(queue, edge->dst, current->bfs + 1);
	}
}

int			skip_reconstruct(t_edge *edge, t_node_ptr ptr)
{
	if (edge->backward->dst->traversal_state == STATE_IN_CROSS)
	{
		if (edge->mark != MARK_BACKWARD_PATH)
			return (TRUE);
	}
	else if (is_in_path(edge, ptr) == FALSE)
		return (TRUE);
	if (edge->dst->is_end_node == FALSE)
		edge->dst->traversal_state = STATE_IN_PATH;
	return (FALSE);
}

int			reconstruct_way(t_node_ptr ptr, t_way *way, t_vector *nodes)
{
	t_edge	*edge;
	int		i;

	*way = init_way();
	i = -1;
	while (++i < ptr->links.size)
	{
		edge = get_from_vec(&ptr->links, i);
		edge = edge->backward;
		if (skip_reconstruct(edge, ptr))
			continue ;
		push_front_vec(&way->nodes, &ptr);
		push_front_vec(&way->edges, &edge);
		way->is_have_backward_edges = way->is_have_backward_edges ||
				edge->mark == MARK_BACKWARD_PATH;
		ptr = edge->backward->dst;
		i = -1;
		if (edge->backward->dst->is_start_node)
			return (finish_reconstruct(way, edge, nodes));
	}
	return (FALSE);
}

int			find_by_bfs(t_node_ptr src, t_way *way, t_vector *nodes)
{
	t_node_ptr	current;
	t_queue		*queue;
	int			res;

	queue = NULL;
	queue_up(&queue, src, 1);
	while (queue != NULL)
	{
		current = dequeue(&queue);
		if (current->traversal_state == STATE_VISITED)
		{
			free(current);
			continue ;
		}
		if (current->is_end_node)
		{
			res = reconstruct_way(current, way, nodes);
			reset_state(nodes, STATE_IN_PATH);
			clear_queue(queue);
			return (res);
		}
		set_bfs_children(&queue, current);
		current->traversal_state = STATE_VISITED;
	}
	return (FALSE);
}
