/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   work_with_way2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmyrcell <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/28 22:51:22 by tmyrcell          #+#    #+#             */
/*   Updated: 2020/11/28 22:51:23 by tmyrcell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

int		is_in_path(t_edge *edge, t_node_ptr src)
{
	if (edge->capacity == 0)
		return (FALSE);
	if (edge->backward->dst->bfs != src->bfs - 1)
		return (FALSE);
	if (edge->backward->dst->traversal_state == STATE_VISITED)
		return (TRUE);
	return (FALSE);
}

int		finish_reconstruct(t_way *way, t_edge *edge, t_vector *nodes)
{
	push_front_vec(&way->nodes, &edge->backward->dst);
	direct_and_mark_way_edges(way);
	reset_state(nodes, STATE_IN_PATH);
	return (TRUE);
}

t_way	*get_place_for_way(t_vector *vec)
{
	if (vec->size == vec->capacity)
		expand_vec(vec, vec->capacity * 2);
	++vec->size;
	return (get_last(vec));
}

t_way	*get_last_way(t_vector *vec)
{
	return (get_last(vec));
}
