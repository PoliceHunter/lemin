/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_edges.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmyrcell <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/28 22:49:57 by tmyrcell          #+#    #+#             */
/*   Updated: 2020/11/28 22:49:58 by tmyrcell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void	set_backward_edge(t_node_ptr src, t_edge *edge)
{
	int		candidate_index;
	t_edge	*candidate;

	if (edge->backward != NULL)
		return ;
	candidate_index = -1;
	while (++candidate_index < edge->dst->links.size)
	{
		candidate = get_from_vec(&edge->dst->links, candidate_index);
		if (candidate->dst != src)
			continue ;
		edge->backward = candidate;
		edge->backward->backward = edge;
		break ;
	}
}

void	set_backward_edges(t_vector *nodes)
{
	int			node_index;
	int			edge_index;
	t_node_ptr	node;

	node_index = -1;
	while (++node_index < nodes->size)
	{
		node = get_from_vec(nodes, node_index);
		edge_index = -1;
		while (++edge_index < node->links.size)
			set_backward_edge(node, get_from_vec(&node->links, edge_index));
	}
}
