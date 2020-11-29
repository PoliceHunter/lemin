/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   direct_edges.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmyrcell <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/28 22:52:13 by tmyrcell          #+#    #+#             */
/*   Updated: 2020/11/28 22:52:15 by tmyrcell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void	disable_edge(t_edge *edge)
{
	edge->capacity = 0;
	edge->backward->capacity = 0;
	edge->mark = MARK_DISABLE;
	edge->backward->mark = MARK_DISABLE;
}

void	direct_edge(t_edge *edge)
{
	edge->capacity = 0;
	edge->backward->capacity = 1;
}

void	mark_edge(t_edge *edge)
{
	edge->mark = MARK_FORWARD_PATH;
	edge->backward->mark = MARK_BACKWARD_PATH;
}

void	direct_and_mark_way_edges(t_way *way)
{
	t_edge	*edge;
	int		i;

	i = -1;
	while (++i != way->edges.size)
	{
		edge = *(t_edge **)get_from_vec(&way->edges, i);
		if (edge->mark == MARK_BACKWARD_PATH)
		{
			disable_edge(edge);
			continue ;
		}
		direct_edge(edge);
		mark_edge(edge);
	}
}
