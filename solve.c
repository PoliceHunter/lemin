/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   solve.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksean <ksean@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/24 18:24:33 by ksean             #+#    #+#             */
/*   Updated: 2020/11/15 12:37:04 by tmyrcell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void	print_way(t_way *way)
{
	t_node_ptr	*ptr;
	int			i;

	i = -1;
	while (++i != way->nodes.size)
	{
		ptr = get_from_vec(&way->nodes, i);
		ft_printf("%s(%d),", (*ptr)->name, (*ptr)->traversal_state);
	}
	ft_printf("\n");
}

void	printf_ways(t_vector ways)
{
	int i;

	i = -1;
	while (++i != ways.size)
	{
		print_way((t_way *)get_from_vec(&ways, i));
	}
}

t_edge	*get_reverse_edge(t_node_ptr node, int expect_state)
{
	t_edge	*edge;
	int		i;

	i = -1;
	while (++i < node->links.size)
	{
		edge = get_from_vec(&node->links, i);
		if (expect_state != STATE_NONE &&
		edge->dst->traversal_state != expect_state)
			continue ;
		if (edge->mark != MARK_BACKWARD_PATH
			|| edge->capacity == 0
			|| edge->dst->is_start_node)
			continue ;
		return (edge);
	}
	return (NULL);
}

void	mark_ways(t_vector *ways)
{
	int i;
	t_way *way;

	i = -1;
	while (++i != ways->size - 1)
	{
		way = get_from_vec(ways, i);
		for (int j = 1; j != way->nodes.size - 1; j++)
		{
			(*(t_node_ptr *) get_from_vec(&way->nodes, j))->traversal_state = STATE_IN_PATH;
		}
	}
}

void	free_way(t_way *way)
{
	free_vec(&way->nodes);
	free_vec(&way->edges);
	free(way);
}

void	free_ways(t_vector *ways)
{
	while (ways->size != 0)
		free_way(pop_back_vec(ways));
	free_vec(ways);
}

int		solve(t_node_ptr src, int ants_count, t_vector *nodes, char **history) {
	t_solver_helper helper;
	t_vector ways;
	t_way way;

	helper = init_helper();
	ways = new_vector(10, sizeof(t_way));
	while (find_by_bfs(src, &way, nodes)) {
		if (way.is_have_backward_edges == TRUE) {
			if (ways.size != 0 && try_candidate(&helper, src, ants_count, ways))
				ways = new_vector(10, sizeof(t_way));
			refresh_state(&ways, nodes);
			free_vec(&way.nodes);
			free_vec(&way.edges);
			continue;
		}

		push_back_vec(&ways, &way);
		mark_ways(&ways);
		if (is_cross(&ways) != FALSE)
			break;
	}
	if (try_candidate(&helper, src, ants_count, ways) == FALSE)
		free_ways(&ways);

	if (history != NULL)
		*history = calculate_best_history(&helper, src, ants_count);
	free_ways(&helper.best_ways);
	return (helper.best_ant_step);
}
